/*
** my.hpp for B-YEP-400-COT-zappy-julcinia.oke
**
** Made by ShadowedSlayer01
** Login <joseph.behanzin@epitech.eu>
**
** Started on  Mon June 02 8:56:19 PM 2025 ShadowedSlayer01
** Last update Mon June 02 10:30:41 PM 2025 ShadowedSlayer01
*/

#ifndef MY_GUI_
    #define MY_GUI_
    #include "my_include.hpp"
    #include "my_define.hpp"
    #include "struct.hpp"
    #include "guimanager.hpp"
    #include "client.hpp"

    #include <stdexcept> 

class ParsingError : public std::runtime_error {
public:
    ParsingError(const std::string& message)
        : std::runtime_error(message) {}
};
#endif /* MY GUI */
