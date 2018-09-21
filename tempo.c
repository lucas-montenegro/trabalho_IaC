#include <stdio.h>
#include <unistd.h>

int main() {
  int i = 1;

  while(i <= 10) {
    printf("%d\n", i);
    i++;
    sleep(1);
  }



  return 0;
}
