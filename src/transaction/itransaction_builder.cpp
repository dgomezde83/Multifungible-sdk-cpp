#include "transaction/itransaction_builder.h"

ITransactionBuilder::ITransactionBuilder() :
        m_version(DEFAULT_VERSION),
        m_options(DEFAULT_OPTIONS)
{}

Transaction ITransactionBuilder::buildSigned(const bytes &seed)
{
    Signer signer(seed);
    Transaction tx = this->build();
    tx.sign(signer);

    return tx;
}

Transaction ITransactionBuilder::buildSigned(const ISecretKey &wallet)
{
    bytes seed = wallet.getSeed();
    Signer signer(seed);
    Transaction tx = this->build();
    tx.sign(signer);

    return tx;
}

ITransactionBuilder &ITransactionBuilder::withVersion(uint64_t version)
{
    m_version = version;
    return *this;
}

ITransactionBuilder &ITransactionBuilder::withOptions(uint32_t options)
{
    m_options = std::make_shared<uint32_t>(options);
    return *this;
}

ITokenTransactionBuilder::ITokenTransactionBuilder() :
        ITransactionBuilder(),
        m_contractCall("")
{}

ITokenTransactionBuilder &ITokenTransactionBuilder::withContractCall(ContractCall contractCall)
{
    m_contractCall = std::move(contractCall);
    return *this;
}
