#include <AsymKey/AsymKeyImpl.h>
#include <stdexcept>

void AsymKeyImpl::_assign_privat_key()
{
    if (!EVP_PKEY_assign_EC_KEY(m_prikey.get(), p_eckey))
        throw std::runtime_error("Error generating private key from public key");
}

AsymKeyImpl::~AsymKeyImpl()
{
    p_eckey = nullptr;
}

AsymKeyImpl::AsymKeyImpl()
: m_prikey(EVP_PKEY_new(), &EVP_PKEY_free)
, p_eckey(EC_KEY_new_by_curve_name(OBJ_txt2nid("secp256k1")))
{
    EC_KEY_set_asn1_flag(p_eckey, OPENSSL_EC_NAMED_CURVE);
    if (!(EC_KEY_generate_key(p_eckey)))
        throw std::runtime_error("Error generate public key");

    _assign_privat_key();
}

AsymKeyImpl::AsymKeyImpl(const AsymKeyImpl& crOther)
: m_prikey(EVP_PKEY_new(), ::EVP_PKEY_free)
, p_eckey(EC_KEY_new_by_curve_name(OBJ_txt2nid("secp256k1")))
{
    if (!EC_KEY_copy(p_eckey, crOther.p_eckey))
        throw std::runtime_error("Error copying public key");
    _assign_privat_key();
}

AsymKeyImpl& AsymKeyImpl::operator=(const AsymKeyImpl& crOther)
{
    if (this != &crOther) {
        if (!EC_KEY_copy(p_eckey, crOther.p_eckey))
            throw std::runtime_error("Error copying public key");
        _assign_privat_key();
    }
    return *this;
}


/// ECKey import export
/// https://stackoverflow.com/questions/50479284/openssl-read-an-ec-key-then-write-it-again-and-its-different
/// https://www.openssl.org/docs/man1.1.0/man3/PEM_read_bio.html

std::string AsymKeyImpl::getPublicKeyPEMStr()  const
{
    BIO_ptr outbio (BIO_new(BIO_s_mem()),&BIO_free_all);
    if (!PEM_write_bio_PUBKEY(outbio.get(), m_prikey.get()))
        throw std::runtime_error("Error writting public key");
    
    const int pubKeyLen = BIO_pending(outbio.get());
    std::string pubkey_str(pubKeyLen, '0');
    BIO_read(outbio.get(), (void*)&(pubkey_str.front()), pubKeyLen);

    return std::move(pubkey_str);
}

std::string AsymKeyImpl::getPrivateKeyPEMStr() const
{
    BIO_ptr outbio(BIO_new(BIO_s_mem()), &BIO_free_all);
    if(!PEM_write_bio_PrivateKey(outbio.get(), m_prikey.get(), NULL, NULL, 0, 0,NULL))
        throw std::runtime_error("Error writting private key");

    const int privKeyLen = BIO_pending(outbio.get());
    std::string privkey_str(privKeyLen, '0');
    BIO_read(outbio.get(), (void*)&(privkey_str.front()), privKeyLen);

    return std::move(privkey_str);
}

void AsymKeyImpl::setPEMPrivateKey(const std::string& crPEMStr)
{
    BIO_ptr bio(BIO_new(BIO_s_mem()), &BIO_free_all);
    const int bio_write_ret = BIO_write(bio.get(), static_cast<const char*>(crPEMStr.c_str()), (int)crPEMStr.size());
    if (bio_write_ret <= 0)
        throw std::runtime_error("Error reading PEM string");

    EVP_PKEY* raw_tmp_priv_pkey = EVP_PKEY_new();
    if (!PEM_read_bio_PrivateKey(bio.get(), &raw_tmp_priv_pkey, NULL, NULL))
        throw std::runtime_error("Error reading private key");

    p_eckey = EVP_PKEY_get1_EC_KEY(raw_tmp_priv_pkey);
    if(!p_eckey)
        throw std::runtime_error("Error importing ec key from private key");

    EC_KEY_set_asn1_flag(p_eckey, OPENSSL_EC_NAMED_CURVE);

    _assign_privat_key();
}