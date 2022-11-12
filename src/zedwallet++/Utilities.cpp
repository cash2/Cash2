// Copyright (c) 2018-2019, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.

//////////////////////////////////
#include <zedwallet++/Utilities.h>
//////////////////////////////////

#include <cmath>
#include <config/WalletConfig.h>
#include <fstream>
#include <iostream>
#include <utilities/ColouredMsg.h>
#include <utilities/PasswordContainer.h>
#include <utilities/String.h>

namespace ZedUtilities
{
    void confirmPassword(const std::shared_ptr<WalletBackend> walletBackend, const std::string msg)
    {
        const std::string currentPassword = walletBackend->getWalletPassword();

        /* Password container requires an rvalue, we don't want to wipe our current
           pass so copy it into a tmp string and std::move that instead */
        std::string tmpString = currentPassword;

        Tools::PasswordContainer pwdContainer(std::move(tmpString));

        while (!pwdContainer.read_and_validate(msg))
        {
            std::cout << WarningMsg("Incorrect password! Try again.") << std::endl;
        }
    }
} // namespace ZedUtilities