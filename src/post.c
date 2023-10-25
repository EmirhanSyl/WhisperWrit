#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/post.h"

static const char *const mode_names[] = {
    [NORMAL] = "NORMAL",
    [WHISPER] = "WHISPER"};

Post sendPostman(int id, Person sender, Person reciever, Letter letter,  MODE mode){
    Post post;
    post.id = id;
    post.sender = sender;
    post.reciever = reciever;
    post.letter = letter;
    post.mode = mode;

    insertPostman(post);
    loadPosts();
    return post;
}