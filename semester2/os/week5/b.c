#include <unistd.h>

int main(int argc, char* argv[]){
	execl("/usr/bin/ls", "/usr/bin/ls", NULL);
	return 0;
}
