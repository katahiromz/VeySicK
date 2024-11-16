void vsk_print(const std::string& str);

// generate error message
#define RENUM_ERROR_MESSAGE(msg) vsk_print(std::string(msg))
// append newline
#undef RENUM_APPEND_NEWLINE
