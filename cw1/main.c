#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>



#include "change_text.h"
#include "cmps.h"
#include "structures.h"


int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wprintf(L"Course work for option 5.2, created by Yurii Serbinovskii.\n");
    
    wint_t order;
    wscanf(L"%ld", &order);
    wchar_t cur_symb = getwchar();


    if (order > 5 || order < 0) {
        fwprintf(stderr, L"Error: Некорркетное число\n");
        exit(0);
    }
    else if (order == 5) {
        wprintf(L"Опция 0: вывести все неповторяющиеся предложения.\n");
        wprintf(L"Опция 1: вывести все предложения, в которых каждое слово удовлетворяет введенной строке-условию. Строка условия содержит: символы, * - 0 или больше любых символов, ? – один любой символ. В строке-условия не может быть больше одного *.\n");
        wprintf(L"Опция 2: отсортировать предложения по средней длине слов в предложении.\n");
        wprintf(L"Опция 3: преобразовать предложения так, чтобы слова располагались в порядке уменьшения длины слова.\n");
        wprintf(L"Опция 4: удалить все предложения, в котором больше 5 или меньше 2 слов.\n");
        exit(0);
    }


    struct Text *text = malloc(sizeof(struct Text));
    text->t = (struct Sentence**)malloc(sizeof(struct Sentence*));
    text->t[0] = malloc(sizeof(struct Sentence));
    wchar_t* cur_sent = (wchar_t*)malloc(sizeof(wchar_t));
    if (text->t == NULL || text->t[0] == NULL || cur_sent == NULL) {
        fwprintf(stderr, L"Error: Ошибка выделения памяти");
        exit(0);
    }
    int sent_index = 0;
    wchar_t delims[5] = L",. \t\n";


    while (1) {
        
        cur_symb = getwchar();
        wchar_t past_symb;

        while (iswspace(cur_symb) || cur_symb == L',')
        {
            past_symb = cur_symb;
            cur_symb = getwchar();
            if (cur_symb == L'\n' && past_symb == L'\n')
                break;
        }

        if (cur_symb == L'\n' && past_symb == L'\n')
            break;
        int symb_index = 0;
        

        for (int i = 0; (cur_symb != L'.'); i++) {
            cur_sent[symb_index] = cur_symb;
            symb_index++;

            past_symb = cur_symb;
            cur_symb = getwchar();
            if (cur_symb == L'\n' && past_symb == L'\n')
                break;

            cur_sent = realloc(cur_sent, (symb_index+1)*sizeof(wchar_t));
            if (cur_sent == NULL) {
                fwprintf(stderr, L"Error: Ошибка выделения памяти");
                exit(0);
            }
        }
        if (past_symb != L'\n') {
            cur_sent[symb_index] = L'\n';
            cur_sent = realloc(cur_sent, sizeof(wchar_t)*(++symb_index+1));
            if (cur_sent == NULL) {
                fwprintf(stderr, L"Error: Ошибка выделения памяти");
                exit(0);
            }
        }
        cur_sent[symb_index] = L'\0';



        if (check_repeats(cur_sent, text->t, sent_index)) {
            text->t[sent_index]->s = cur_sent;
            sent_index++;
            text->t = realloc(text->t, (sent_index+1)*sizeof(struct Sentence*));
            text->t[sent_index] = malloc(sizeof(struct Sentence));
            if (text->t == NULL || text->t[sent_index] == NULL) {
                fwprintf(stderr, L"Error: Ошибка выделения памяти");
                exit(0);
            }
        }
        cur_sent = malloc(sizeof(wchar_t));
        if (cur_sent == NULL) {
            fwprintf(stderr, L"Error: Ошибка выделения памяти");
            exit(0);
        }
        if (cur_symb == L'\n')
            break;
    }
    free(cur_sent);
    wchar_t* mask;
    int* bad_memory;
    int star_count = 0;
    
    switch (order)
    {
        case 0:
            for(int i = 0; i < sent_index; i++) {
                wprintf(L"%ls.", text->t[i]->s);
            }
            break;
        case 1:
            star_count = 0;
            mask = malloc(sizeof(wchar_t));
            if (mask == NULL) {
                fwprintf(stderr, L"Error: Ошибка выделения памяти");
                exit(0);
            }
            wchar_t cur_symb = getwchar();
            if (cur_symb == L'*')
                star_count++;
            int mask_len = 0;
            while (cur_symb != L'\n')
            {
                mask[mask_len++] = cur_symb;
                mask = realloc(mask, sizeof(wchar_t)*(mask_len+1));
                if (mask == NULL) {
                    fwprintf(stderr, L"Error: Ошибка выделения памяти");
                    exit(0);
                }
                cur_symb = getwchar();
                if (cur_symb == L'*')
                    star_count++;
                if (star_count > 1){
                    fwprintf(stderr, L"Error: Слишком много *\n");
                    exit(0);
                }
            }
    
            mask[mask_len] = '\0';
            for (int i = 0; i<sent_index; i++) {
                if (mask_approved(text->t[i]->s, mask)) {
                    wprintf(L"%ls.", text->t[i]->s);
                }
            }
            free(mask);
            break;
        case 2:
            qsort(text->t, sent_index, sizeof(struct Sentence*), cmp);
            for (int i = 0; i < sent_index; i++) {
                wprintf(L"%ls.", text->t[i]->s);
            }
            break;
        case 3:
            for (int i = 0; i < sent_index; i++) {
                words_sort(text->t[i]->s);
            }
            for (int i = 0; i < sent_index; i++) {
                wprintf(L"%ls.", text->t[i]->s);
            }
            break;
        case 4:
            bad_memory = malloc(sizeof(int)*sent_index);
            if (bad_memory == NULL) {
                fwprintf(stderr, L"Error: Ошибка выделения памяти");
                exit(0);
            }
            int bad_count = 0;
            for (int i = 0; i < sent_index; i++){
                if (delete_sent(text->t[i]->s)) {
                    bad_memory[i] = i;
                    free(text->t[i]->s);
                    free(text->t[i]);
                }
                else
                    bad_memory[i] = -1;
            }
                for (int i = 0; i < sent_index; i++) {
                    if (bad_memory[i] == -1)
                        wprintf(L"%ls.", text->t[i]->s);
                }
            for (int i = 0; i < sent_index; i++) {
                if (bad_memory[i] == -1){
                    free(text->t[i]->s);
                    free(text->t[i]);
                }
            }
            break;
        default:
            break;
    } 

    for (int i = 0; i < sent_index; i++) {
        if (order != 4){
            free(text->t[i]->s);
            free(text->t[i]);
        }
    }
    free(text->t);
    free(text);

    return 0;
}