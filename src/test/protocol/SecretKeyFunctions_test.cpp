#include <xrpl/beast/unit_test.h>
#include <xrpl/beast/utility/rngfill.h>
#include <xrpl/crypto/csprng.h>
#include <xrpl/protocol/PublicKey.h>
#include <xrpl/protocol/SecretKey.h>
#include <xrpl/protocol/digest.h>
#include <xrpl/protocol/Seed.h>
#include <xrpl/protocol/detail/secp256k1.h>
#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace ripple {

class SecretKeyFunctions_test : public beast::unit_test::suite
{
public:
    void
    testSecp256k1KeyGeneration()
    {
        testcase("Secp256k1 Key Generation");

        auto sk = randomSecp256k1SecretKey();
        BEAST_EXPECT(sk.size() == 32); // Secret key should be 32 bytes

        auto pk = derivePublicKey(KeyType::secp256k1, sk);
        BEAST_EXPECT(pk.size() != 0); // Public key should not be empty
        BEAST_EXPECT(pk.size() == 33); // Compressed public key should be 33 bytes
    }

    void
    testEd25519KeyGeneration()
    {
        testcase("Ed25519 Key Generation");

        auto sk = randomEd25519SecretKey();
        BEAST_EXPECT(sk.size() == 32); // Secret key should be 32 bytes

        auto pk = derivePublicKey(KeyType::ed25519, sk);
        BEAST_EXPECT(pk.size() != 0); // Public key should not be empty
        BEAST_EXPECT(pk.size() == 33); // Public key should be 33 bytes
    }

    void
    testDilithiumKeyGeneration()
    {
        testcase("Dilithium Key Generation");

        auto seed = randomSeed();
        auto sk = randomDilithiumSecretKey(seed);
        BEAST_EXPECT(sk.size() == 2528); // Secret key size

        auto pk = derivePublicKey(KeyType::dilithium, sk, seed);
        BEAST_EXPECT(pk.size() == 1312); // Public key size
    }

    void
    testSecp256k1Signing()
    {
        testcase("Secp256k1 Signing");

        auto keyPair = randomKeyPair(KeyType::secp256k1);
        auto const& sk = keyPair.second;
        auto const& pk = keyPair.first;

        std::string message = "test message";
        uint256 digest = sha512Half(Slice{message.data(), message.size()});
        auto sig = signDigest(pk, sk, digest);

        BEAST_EXPECT(sig.size() != 0); // Signature should not be empty
        BEAST_EXPECT(sig.size() <= 72); // DER-encoded signature length
    }

    void
    testEd25519Signing()
    {
        testcase("Ed25519 Signing");

        auto keyPair = randomKeyPair(KeyType::ed25519);
        auto const& sk = keyPair.second;
        auto const& pk = keyPair.first;

        std::string message = "test message";
        auto sig = sign(pk, sk, Slice{message.data(), message.size()});

        BEAST_EXPECT(sig.size() != 0); // Signature should not be empty
        BEAST_EXPECT(sig.size() == 64); // Ed25519 signature length
    }

    void
    testDilithiumSigning()
    {
        testcase("Dilithium Signing");

        auto keyPair = randomKeyPair(KeyType::dilithium);
        auto const& sk = keyPair.second;
        auto const& pk = keyPair.first;

        std::string message = "test message";
        auto sig = sign(pk, sk, Slice{message.data(), message.size()});

        BEAST_EXPECT(sig.size() != 0); // Signature should not be empty
        BEAST_EXPECT(sig.size() == 2420); // Dilithium signature length
    }

void
    testSecp256k1Transaction()
    {
        testcase("Secp256k1 Full Transaction Process");

        // Step 1: Key Generation
        auto keyPair = randomKeyPair(KeyType::secp256k1);
        auto const& sk = keyPair.second;
        auto const& pk = keyPair.first;

        BEAST_EXPECT(sk.size() != 0);
        BEAST_EXPECT(pk.size() != 0);

        // Step 2: Message Signing
        std::string message = "This is a test transaction for secp256k1.";
        uint256 digest = sha512Half(Slice{message.data(), message.size()});
        auto sig = signDigest(pk, sk, digest);

        BEAST_EXPECT(sig.size() != 0);

        // Step 3: Signature Verification
        bool isValid = verifyDigest(pk, digest, sig);
        BEAST_EXPECT(isValid); // Signature should be valid
    }

    void
    testEd25519Transaction()
    {
        testcase("Ed25519 Full Transaction Process");

        // Step 1: Key Generation
        auto keyPair = randomKeyPair(KeyType::ed25519);
        auto const& sk = keyPair.second;
        auto const& pk = keyPair.first;

        BEAST_EXPECT(sk.size() != 0);
        BEAST_EXPECT(pk.size() != 0);

        // Step 2: Message Signing
        std::string message = "This is a test transaction for ed25519.";
        auto sig = sign(pk, sk, Slice{message.data(), message.size()});

        BEAST_EXPECT(sig.size() != 0);

        // Step 3: Signature Verification
        bool isValid = verify(pk, Slice{message.data(), message.size()}, sig);
        BEAST_EXPECT(isValid); // Signature should be valid
    }

    void
    testDilithiumTransaction()
    {
        testcase("Dilithium Full Transaction Process");

        // Step 1: Key Generation
        auto seed = randomSeed();
        auto sk = randomDilithiumSecretKey(seed);
        auto pk = derivePublicKey(KeyType::dilithium, sk, seed);

        BEAST_EXPECT(sk.size() != 0);
        BEAST_EXPECT(pk.size() != 0);

        // Step 2: Message Signing
        std::string message = "This is a test transaction for dilithium.";
        auto sig = sign(pk, sk, Slice{message.data(), message.size()});

        BEAST_EXPECT(sig.size() != 0);

        // Step 3: Signature Verification
        bool isValid = verify(pk, Slice{message.data(), message.size()}, sig);
        BEAST_EXPECT(isValid); // Signature should be valid
    }

    void
    testDilithiumKeyPairgeneration()
    {
        testcase("Dilithium Random Key Pair Generation and Public Key Derivation");
        // Case 1 : Generate random keypair using randomKeyPiar and compare derived public key
        {
            auto randomSeedValue = randomSeed();
            auto sk = randomDilithiumSecretKey(randomSeedValue);
            auto pk = derivePublicKey(KeyType::dilithium, sk, randomSeedValue);

            // Derive the public key again and compare
            auto derivedPk = derivePublicKey(KeyType::dilithium, sk, randomSeedValue);
            BEAST_EXPECT(pk == derivedPk); // Public keys should match
        }

        // Case 2 : Generate a keypair with deterministic seed and compare derived publick key
        {
            auto const deterministicSeed = generateSeed("masterpassphrase");
            auto sk = generateSecretKey(KeyType::dilithium, deterministicSeed);
            auto pk = derivePublicKey(KeyType::dilithium, sk, deterministicSeed);

            

            auto keyPair = generateKeyPair(KeyType::dilithium, deterministicSeed);
            auto const& sk1 = keyPair.second;
            auto const& pk1 = keyPair.first;

            auto derivedPk = derivePublicKey(KeyType::dilithium, sk1, deterministicSeed);

            BEAST_EXPECT(pk == derivedPk); // PublicKeys should match
            BEAST_EXPECT(pk1 == derivedPk);

        }

        // Case 3 : Generate a random secret key and deterministic secret key , try to compare the derivation
        {
            auto const seed = randomSeed();
            auto sk = randomDilithiumSecretKey(seed);
            auto pk = derivePublicKey(KeyType::dilithium, sk, seed);

            auto keyPair = generateKeyPair(KeyType::dilithium, seed);
            auto const& sk1 = keyPair.second;
            auto const& pk1 = keyPair.first;

            auto derivedPk = derivePublicKey(KeyType::dilithium, sk1, seed);

            BEAST_EXPECT(pk == derivedPk); // PublicKeys should match
            BEAST_EXPECT(pk1 == derivedPk);
        }
    }



    void
    run() override
    {
        testSecp256k1KeyGeneration();
        testEd25519KeyGeneration();
        testDilithiumKeyGeneration();
        testSecp256k1Signing();
        testEd25519Signing();
        testDilithiumSigning();
        testDilithiumTransaction();
        testSecp256k1KeyGeneration();
        testSecp256k1Transaction();
        testDilithiumKeyPairgeneration();
 
    }
};

BEAST_DEFINE_TESTSUITE(SecretKeyFunctions, protocol, ripple);

}  // namespace ripple