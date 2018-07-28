Ex.1:

int listSum(int cutValue, node *nodePtr) {
    int sum = 0;
    while(nodePtr) {
        sum += nodePtr->value > cutValue ? nodePtr->value : 0;
        nodePtr = nodePtr->next;
    }
    return sum;
}




Ex.2

A) 0
B) Won't compile, a is an int and cannot be treated as a pointer.
C) 3
D) Won't compile, a is an int reference and can only be treated as an int.
E) 5
F) Won't compile, you can't use an int as a pointer without the proper cast.
G) Won't compile, &a is an int pointer, and func expects an int.
H) Won't compile, func expects an int pointer and is receiving an int.




Ex.3

Let str_ be the original string,

str points at str_[1]
str2 at str_[4]
str3 at str_[3]
str4 at str_[13]

None are valid, as they are trying to free memory inside an malloc'ed area. This is a very bad idea by itself, but in addition, if the first free would have worked, the other two would be re-freeing portions of this memory.




Ex.4

That snippet of code is greyscaling the entire screen, but giving more weight to the green, a bit less to the red and even less to the blue component of each pixel.




Ex.5



int getMissing(int* array, unsigned int size) {
    unsigned int sum = (size+1) * (size+2) / 2;
    
    for (unsigned int i = 0; i < size; i++)
        sum -= array[i];
    
    return sum;
}

Only in case, I'm ussing Gauss' summation for getting the sum of all the numbers from 1 to (size+1), then substract all the array elements so it's only left the missing one.




Ex.6

std::vector<std::string> split(const std::string& str) {
    std::list<std::string> words;
    unsigned int lastBegin = 0;
    for (unsigned int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            if (i-lastBegin > 0)
                words.push_back(str.substr(lastBegin, i-lastBegin));
            lastBegin = i+1;
        }
    }
    if (str.size()-lastBegin-1 > 0)
        words.push_back(str.substr(lastBegin, str.size()-lastBegin));
    
    return { make_move_iterator(begin(words)), make_move_iterator(end(words)) };
}
