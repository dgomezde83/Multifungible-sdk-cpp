#include "UnitTestsInfo.h"

/*-------------------------------------------------------------------------*
*--------------------------------------------------------------------------*
*-------------------------------------------------------------------------*/

TEST_F(FixtureOverUnitTests, issueCollectionVerificationSFT) {
    EXPECT_EQ(m_ut->issueCollectionVerification(MULTIFUNGIBLE_MAINWALLET,
                                                   WALLETPASSWORD,
                                                   false,
                                                   "collectionTest",
                                                   "CTST",
                                                   true,true,true,true,true,true,true), true);
}

/*-------------------------------------------------------------------------*
*--------------------------------------------------------------------------*
*-------------------------------------------------------------------------*/

//With a wallet not present in the blockchain
TEST_F(FixtureOverUnitTests, issueCollectionVerificationSFTNotInBlockchain)
{
    returnCodeAndChar t_rccLoad = Multifungible::loadWallet(MULTIFUNGIBLE_WALLET_NOTINBLOCKCHAIN,WALLETPASSWORD);
    try
    {

    m_ut->issueCollectionVerification(MULTIFUNGIBLE_WALLET_NOTINBLOCKCHAIN,
                                                   WALLETPASSWORD,
                                                   false,
                                                   "collectionTest",
                                                   "CTST",
                                                   true,true,true,true,true,true,true);
    FAIL();
    }
    catch( const std::runtime_error& err )
    {
        // check exception
        std::string t_expected = std::string(MULTIVERSX_ADDRESS_NOT_IN_BLOCKCHAIN) + std::string(t_rccLoad.message);
        std::string t_received = std::string(err.what()).substr(0,strlen(MULTIVERSX_ADDRESS_NOT_IN_BLOCKCHAIN) + strlen(t_rccLoad.message));
        if (__SIMULATE__)
        {
            SUCCEED();
        }
        else
        {
            ASSERT_STRCASEEQ( t_expected.c_str(), t_received.c_str());
        }
    }
}

/*-------------------------------------------------------------------------*
*--------------------------------------------------------------------------*
*-------------------------------------------------------------------------*/

//With a wallet with no money
TEST_F(FixtureOverUnitTests, issueCollectionVerificationSFTNoMoney)
{
    try
    {

    m_ut->issueCollectionVerification(MULTIFUNGIBLE_WALLET_NOMONEY,
                                                   WALLETPASSWORD,
                                                   false,
                                                   "collectionTest",
                                                   "CTST",
                                                   true,true,true,true,true,true,true);
    FAIL();
    }
    catch( const std::runtime_error& err )
    {
        // check exception
        if (__SIMULATE__)
        {
            SUCCEED();
        }
        else
        {
            ASSERT_STRCASEEQ( MULTIVERSX_INSUFFICIENT_FUNDS, err.what());
        }
    }
}

/*-------------------------------------------------------------------------*
*--------------------------------------------------------------------------*
*-------------------------------------------------------------------------*/

//Only give add role property: p_canAddSpecialRoles
TEST_F(FixtureOverUnitTests, issueCollectionVerificationSFTOnlyAddRole) {
    EXPECT_EQ(m_ut->issueCollectionVerification(MULTIFUNGIBLE_MAINWALLET,
                                                   WALLETPASSWORD,
                                                   false,
                                                   "collectionTest",
                                                   "CTST",
                                                   false,false,false,false,false,false,true), true);
}

/*-------------------------------------------------------------------------*
*--------------------------------------------------------------------------*
*-------------------------------------------------------------------------*/

//Give no roles
TEST_F(FixtureOverUnitTests, issueCollectionVerificationSFTNoRoles) {
    EXPECT_EQ(m_ut->issueCollectionVerification(MULTIFUNGIBLE_MAINWALLET,
                                                   WALLETPASSWORD,
                                                   false,
                                                   "collectionTest",
                                                   "CTST",
                                                   false,false,false,false,false,false,false), true);
}

