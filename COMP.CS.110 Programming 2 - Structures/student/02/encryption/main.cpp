#include <iostream>
#include <string>

int main()
{
    std::string alphabets = "abcdefghijklmnopqrstuvwxyz";
    std::string encryption_key;
    std::string text;
    std::string encrypted_text;
    int encryption_key_length;
    int text_length;
    int found = 0;

    std::cout << "Enter the encryption key: ";
    std::cin >> encryption_key;
    encryption_key_length = encryption_key.length();
    if (encryption_key.length() != 26) {
        std::cout << "Error! The encryption key must contain 26 characters."
                  << std::endl;
        return EXIT_FAILURE;
    }
    for (int i = 0; i < encryption_key_length; i++) {
        if (isupper(encryption_key[i])) {
            std::cout << "Error! The encryption key must contain only lower "
                         "case characters." << std::endl;
            return EXIT_FAILURE;
        }
    }
    for (char alphabet = 'a'; alphabet < 'z'; alphabet++) {
        for (int j = 0; j < encryption_key_length; j++) {
            if (alphabet == encryption_key[j]) {
                found++;
            }
        }
        if (found != 1) {
            std::cout << "Error! The encryption key must contain all "
                         "alphabets a-z." << std::endl;
            return EXIT_FAILURE;
        }
        found = 0;
    }

    std::cout << "Enter the text to be encrypted: ";
    std::cin >> text;
    text_length = text.length();
    for (int i = 0; i < text_length; i++) {
        if (isupper(text[i])) {
            std::cout << "Error! The text to be encrypted must contain only "
                         "lower case characters." << std::endl;
            return EXIT_FAILURE;
        }
    }

    encrypted_text = text;
    for (int i = 0; i < text_length; i++) {
        encrypted_text.replace(i, 1, 1,
                               encryption_key[alphabets.find(text[i])]);
    }
    std::cout << "Encrypted text: " + encrypted_text << std::endl;
    return EXIT_SUCCESS;
}


