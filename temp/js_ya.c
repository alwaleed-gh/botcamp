#include <stdio.h>

struct Person {
    char name[50];
    int age;
    char city[50];
};


void yaml(struct Person p, char *file_name) {
    FILE *f = fopen(file_name, "a");  
    if (f == NULL) {
        
        return;
    }
    
    fprintf(f, " name: %s\n", p.name);
    fprintf(f, "  age: %d\n", p.age);
    fprintf(f, "  city: %s\n", p.city);
    fclose(f);
}


void json(struct Person p, char *file_name) {
    FILE *f = fopen(file_name, "a"); 
    if (f == NULL) {
        
        return;
    }
    
    fprintf(f, "{\n");
    fprintf(f, "  \"name\": \"%s\",\n", p.name);
    fprintf(f, "  \"age\": %d,\n", p.age);
    fprintf(f, "  \"city\": \"%s\"\n", p.city);
    fprintf(f, "}\n");
    fclose(f);
}

int main() {
    struct Person p1 = {"Ahmed", 28, "Riyadh"};
    struct Person p2 = {"Alwaleed", 99, "Albah"};
    struct Person p3 = {"Ali", 28, "Abha"};
    
    
    yaml(p1, "data.yaml");
    yaml(p2, "data.yaml");
    yaml(p3, "data.yaml");
    
    json(p1, "data.json");
    json(p2, "data.json");
    json(p3, "data.json");
    
  
    
    return 0;
}