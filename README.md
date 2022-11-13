# Math-Parser
A math parser that parses  complex math expressions


[Coverage steps]
make
ASAN_OPTIONS=coverage=1 ./main                  # this will create a *.sancov file in current directory
sancov -symbolize main.7277.sancov main         # symbolize the report
sancov -covered-functions main.7277.sancov main # printf covered functions