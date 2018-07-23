//TODO proper header for program

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define IS_TERMINATOR(x) ((x) == '.' || (x) == '?' || (x) == '?' || IS_SPECIAL(x))
#define IS_SPECIAL(x) ((x) == '0' || (x) == '\n')

#define MAX_SENTENCE_BLOCK_LEN 1000

typedef struct node {
    char* block;
    struct node * next;
} node_t;

static int get_next_sentence(int fd, int max, char* s, int* size) {
    int rc = 0;
    char c = 0;
    int i = 0;

    *size = 0;
    rc = read(fd, &c, sizeof(c));

    while((sizeof(c)== rc)) {
        if(i < max) {
            if(IS_SPECIAL(c)) {
                c = ' ';
            }
            s[i] = c;
        }
        i++;
        if(IS_TERMINATOR(c)) {
            *size = i;
            return 0;
        }
        rc = read(fd, &c, sizeof(c));
    }
    //fprintf(stderr, "Exited without sentence terminator (%x, %d, %d)\n", c, errno, rc);
    return -1;
}

static int save_valid_sentence_block(const char* sentence_block, node_t* list) {
    fprintf(stderr, "Found sentence block! (%s)\n", sentence_block);
    node_t* new_node = malloc(sizeof(node_t));
    char* b = strdup(sentence_block);

    if(!b || !new_node) {
        fprintf(stderr, "out of memory\n");
        return -1;
    }
    new_node->block = b;

    node_t* n = list;
    while(n->next) {
        if(0 > strcmp(n->next->block, b)) {
            n = n->next;
        }
        break;
    }
    node_t* tmp = n->next;
    n->next = new_node;
    n->next->next = tmp;
    return 0;
}

static int dump_sentence_blocks(node_t* list, const char* outpath) {
    int rc;
    node_t* n = list->next;
    int fd = open(outpath, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd < 0) {
        fprintf(stderr, "Failed to open out file (%d)\n", errno);
        return -1;
    }
    while(n) {
        int len = strlen(n->block);
        rc = write(fd, n->block, strlen(n->block));
        if(len != rc) {
            fprintf(stderr, "Failed to write out file (%d)\n", errno);
            close(fd);
            return -1;
        }
        char c = '\n';
        if(sizeof(c) != write(fd, &c, sizeof(c))) {
            fprintf(stderr, "Failed to write out file (%d)\n", errno);
            close(fd);
            return -1;
        }
        n = n->next;
    }
    close(fd);
    return 0;
}

int get_sentences(const char* inpath, const char* outpath, uint32_t min, uint32_t max) {
    int rc = 0;
    node_t* list = malloc(sizeof(node_t));
    if(!inpath || !outpath || min > MAX_SENTENCE_BLOCK_LEN || max > MAX_SENTENCE_BLOCK_LEN) {
        fprintf(stderr, "invalid args\n");
        return -1;
    }

    char* sentence_block = malloc(max);
    char* sentence = malloc(max);
    if(!sentence_block || !sentence || !list) {
        fprintf(stderr, "out of memory\n");
        return -1;
    }
    list->next = NULL;

    //open the inpath
    int fd = open(inpath, O_RDONLY, S_IRUSR);
    if(fd < 0) {
        fprintf(stderr, "Failed to open in file (%d)\n", errno);
        rc = -1;
        goto cleanup;
    }

    //read a character and add it to the buffer, take special action if we reach a terminator
    int curr_block_size = 0;
    int size = 0;
    while(0 == get_next_sentence(fd, max, sentence, &size)) {
        if(size + curr_block_size > max) {
            if(curr_block_size >= min) {
                //we had a valid sentence and our greedy select could not add more, so use this one
                save_valid_sentence_block(sentence_block, list);
            }
            if(size <= max) {
                //move the tail and keep going, we will check if it is valid on the next run
                curr_block_size = size;
                memset(sentence_block, 0, max);
                strncpy(sentence_block, sentence, size);
                continue;
            } else {
                //throw everything out and keep going
                curr_block_size = 0;
                memset(sentence_block, 0, max);
            }
        }
        else {
            //need to keep going to find the next sentence
            strncpy(sentence_block + curr_block_size, sentence, size);
            curr_block_size += size;
            continue;
        }
    }

    //one final check
    if(curr_block_size >= min && curr_block_size <= max) {
        save_valid_sentence_block(sentence_block, list);
    }

    rc = dump_sentence_blocks(list, outpath);
    if(0 != rc) {
        goto cleanup;
    }

    rc = 0;
cleanup:
    free(sentence_block);
    free(sentence);
    return rc;
}

//TODO modularize main, tests, and functionality to separate files at least
int main(int argc, char** argv) {
#define EXPECTED_ARGC 5
    int rc;
    if(EXPECTED_ARGC != argc) {
        fprintf(stderr, "Invalid args (%d != %d)", argc, EXPECTED_ARGC);
        return -1;
    }
    int min = atoi(argv[3]);
    int max = atoi(argv[4]);
    rc = get_sentences(argv[1], argv[2], min, max);
    return rc;
}
