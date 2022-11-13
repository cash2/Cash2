// Copyright (c) 2019, The TurtleCoin Developers
// Copyright (c) 2018-2022 The Cash2 developers
//
// Please see the included LICENSE file for more information.

////////////////////////////
#include <utilities/Input.h>
////////////////////////////

#include <iostream>
#include <utilities/ColouredMsg.h>

namespace Utilities
{
    bool confirm(const std::string &msg)
    {
        return confirm(msg, true);
    }

    /* defaultToYes = what value we return on hitting enter, i.e. the "expected"
       workflow */
    bool confirm(const std::string &msg, const bool defaultToYes)
    {
        /* In unix programs, the upper case letter indicates the default, for
           example when you hit enter */
        const std::string prompt = defaultToYes ? " (Y/n): " : " (y/N): ";

        while (true)
        {
            std::cout << InformationMsg(msg + prompt);

            std::string answer;
            std::getline(std::cin, answer);

            const char c = ::tolower(answer[0]);

            switch (c)
            {
                /* Lets people spam enter / choose default value */
                case '\0':
                    return defaultToYes;
                case 'y':
                    return true;
                case 'n':
                    return false;
            }

            std::cout << WarningMsg("Bad input: ") << InformationMsg(answer)
                      << WarningMsg(" - please enter either Y or N.") << std::endl;
        }
    }
} // namespace Utilities
