#pragma GCC push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

int
main(int argc, char *argv[]) {
  caml_startup(argv);
  // TODO(dinosaure): check if [argv] terminates with [NULL].
  return (0);
}

#pragma GCC pop
