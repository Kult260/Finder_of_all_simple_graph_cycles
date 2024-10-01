#ifndef STRUCTS_H
#define STRUCTS_H

//Перечисление, содержащее коды ошибок
enum ErrorType
{
    INVALID_OPEN_FILE,
    INVALID_KEYWORD,
    INVALID_HEADER,
    INVALID_CURLY_BRACES,
    INVALID_SPACE_BETWEEN_HEADING_AND_CURLY_BRACKET,
    INVALID_COMMUNICATION_BETWEEN_VERTICES,
    INVALID_VERTICE_NAME_OR_SYMBOLS,
    SEMOLON_IS_MISSING,
    INVALID_CONNECTION_SIGN,
    INVALID_SYMBOLS_AFTER_GRAPH_DESCRIPTION,
    INVALID_SAVE_FILE
};

//Структура, содержащая тип ошибки и строку, в которой она была обнаружена
struct Error
{
    ErrorType type;
    int line_num = 0;

    bool operator== (const Error &error)  const{
        return this->type == error.type && this->line_num == error.line_num;
    }
};




#endif // STRUCTS_H
