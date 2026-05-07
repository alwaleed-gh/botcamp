#include<stdio.h>
#include<stdlib.h>

struct car {
    int id;
    int year;
};
int main() {
    void *ptr =  malloc(sizeof(struct car));
    struct car *sptr = (struct car *)ptr;

    sptr->id = 0x44eeff11;
    sptr->year = 0x2020;
     
    FILE *fh = fopen("car.pex", "wb");
    if(fh != NULL) {
     fwrite(sptr, sizeof(struct car), 1, fh);
     fclose(fh);
        
    fh = fopen("car.pex", "rb"); 
    if(fh != NULL) {
        fread(sptr, sizeof(struct car), 1, fh);
        
        fclose(fh);
        
        
        printf("ID: 0x%x\n", sptr->id);
        printf("Year: 0x%x\n", sptr->year);
    }
    }
     free(ptr); 
}

 
