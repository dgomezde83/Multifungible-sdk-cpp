#ifndef JSONHANDLER_WRAPPER_H
#define JSONHANDLER_WRAPPER_H

#include <string>
#include <map>

#include "iwrapper.h"
#include "utils/params.h"
#include "account/address.h"
#include "internal/internal.h"
#include "transaction/transaction.h"

namespace ih
{
namespace wrapper
{
class TransactionInputWrapper : public IWrapper
{
public:
    explicit TransactionInputWrapper(std::map<uint32_t, std::string> const &inputData) :
            IWrapper(inputData)
    {
        m_containsData = (getInputData().find(ARGS_TX_IDX_DATA) != getInputData().end());
        m_containsReceiverName = (getInputData().find(ARGS_TX_IDX_RECEIVER_NAME) != getInputData().end());
        m_containsSenderName = (getInputData().find(ARGS_TX_IDX_SENDER_NAME) != getInputData().end());
        m_containsOptions = (getInputData().find(ARGS_TX_IDX_OPTIONS) != getInputData().end());
    }

    uint64_t getNonce() const
    {
        return std::stoul(getInputData().at(ARGS_TX_IDX_NONCE));
    }

    std::string getValue() const
    {
        return getInputData().at(ARGS_TX_IDX_VALUE);
    }

    Address getReceiver() const
    {
        return Address(getInputData().at(ARGS_TX_IDX_RECEIVER));
    }

    std::shared_ptr<bytes> getReceiverName() const
    {
        return getUserInputIfExists<bytes>(ARGS_TX_IDX_RECEIVER_NAME, m_containsReceiverName);
    }

    std::shared_ptr<bytes> getSenderName() const
    {
        return getUserInputIfExists<bytes>(ARGS_TX_IDX_SENDER_NAME, m_containsSenderName);
    }

    uint64_t getGasPrice() const
    {
        return std::stoul(getInputData().at(ARGS_TX_IDX_GAS_PRICE));
    }

    uint64_t getGasLimit() const
    {
        return std::stoul(getInputData().at(ARGS_TX_IDX_GAS_LIMIT));
    }

    std::shared_ptr<bytes> getData() const
    {
        return getUserInputIfExists<bytes>(ARGS_TX_IDX_DATA, m_containsData);
    }

    std::shared_ptr<std::string> getSignature() const
    {
        return DEFAULT_SIGNATURE;
    }

    std::string getChainId() const
    {
        return DEFAULT_CHAIN_ID;
    }

    uint64_t getVersion() const
    {
        return DEFAULT_VERSION;
    }

    std::string getInputFile() const
    {
        return getInputData().at(ARGS_TX_IDX_PEM_INPUT_FILE);
    }

    std::string getOutputFile() const
    {
        return getInputData().at(ARGS_TX_IDX_JSON_OUT_FILE);
    }

    std::shared_ptr<uint32_t> getOptions() const
    {
        return DEFAULT_OPTIONS;
    }

private:

    template<class T>
    std::shared_ptr<T> getUserInputIfExists(unsigned int const &idx, bool const &exists) const
    {
        if (exists)
        {
            std::string const userInput = getInputData().at(idx);
            bytes const input(userInput.begin(),userInput.end());
            return std::make_shared<T>(input);
        }
        else return nullptr;
    }

    bool m_containsData;
    bool m_containsReceiverName;
    bool m_containsSenderName;
    bool m_containsOptions;
};
}
}

#endif
