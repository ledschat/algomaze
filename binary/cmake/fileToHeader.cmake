string(TOUPPER "${NAME}" header)
string(REGEX REPLACE "[^A-Z]" "_" header "${header}")

file(READ "${INPUTFILE}" output HEX)
file(APPEND "${OUTPUTFILE}" "\n")
file(APPEND "${OUTPUTFILE}" "#ifndef LEDSCHAT_${header}_H_\n")
file(APPEND "${OUTPUTFILE}" "#define LEDSCHAT_${header}_H_\n")
file(APPEND "${OUTPUTFILE}" "\n")
file(APPEND "${OUTPUTFILE}" "namespace LedsChat\n")
file(APPEND "${OUTPUTFILE}" "{\n")
file(APPEND "${OUTPUTFILE}" "    constexpr unsigned char ${NAME}[] = {\n")

string(REGEX REPLACE  "(..)"  "        0x\\1,\n" output "${output}")
string(REGEX REPLACE  ",\n$"  "\n" output "${output}")

file(APPEND "${OUTPUTFILE}" "${output}")

file(APPEND "${OUTPUTFILE}" "    };\n")
file(APPEND "${OUTPUTFILE}" "}\n")
file(APPEND "${OUTPUTFILE}" "\n")
file(APPEND "${OUTPUTFILE}" "#endif\n")