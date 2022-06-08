#include <SFML/Graphics.hpp>
#include "lab_8.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using mt::math::Vec33d;




int Transform_to_int(double (&matrix)[9], std::string stroka){
    int k = 0;
    std::string str;

    for(int i = 0; i < stroka.size(); i++){
        if (stroka[i] != ' '){
            str += stroka[i];
        }
        if (stroka[i] == ' ' && (i != 0)){
            matrix[k] = std::stod(str);
            k += 1;
            str = "";
        }
        if (stroka[i] == '\n'){
            str = "";
        }
    }
};

int main(){

    sf::Texture texture;
    if (!texture.loadFromFile("BackGround.jpg"))
    {
        std::cout << "The photo went for a walk... " << std::endl;
        return -1;
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load the font file.";
        return -1;
    }
    const int width = 1920;
    const int height = 1080;

    sf::Sprite background(texture, sf::IntRect(0, 0, width, height));

    sf::RenderWindow window(sf::VideoMode(width, height), "Calculation");

            sf::Text description;
            description.setFont(font);
            description.setCharacterSize(50);
            description.setOrigin(-500, -100);
            description.setFillColor(sf::Color::Yellow);

            sf::Text addition;
            addition.setFont(font);
            addition.setCharacterSize(50);
            addition.setOrigin(-200, -400);
            addition.setFillColor(sf::Color::Red);

            sf::Text difference;
            difference.setFont(font);
            difference.setCharacterSize(50);
            difference.setOrigin(-700, -400);
            difference.setFillColor(sf::Color::Red);

            sf::Text multiplication;
            multiplication.setFont(font);
            multiplication.setCharacterSize(50);
            multiplication.setOrigin(-1300, -400);
            multiplication.setFillColor(sf::Color::Red);

            sf::Text reverse;
            reverse.setFont(font);
            reverse.setCharacterSize(50);
            reverse.setOrigin(-200, -800);
            reverse.setFillColor(sf::Color::Red);

            sf::Text transposed;
            transposed.setFont(font);
            transposed.setCharacterSize(50);
            transposed.setOrigin(-700, -800);
            transposed.setFillColor(sf::Color::Red);


    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(0, 0));


    while(window.isOpen())
        {
            sf::Event event;

            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();

                sf::Window window2;
                sf::Font arial;
                arial.loadFromFile("arial.ttf");
                sf::Text t_first, t_second, first, second, title_result;
                title_result.setFillColor(sf::Color::Green);
                title_result.setFont(arial);
                title_result.setOrigin(-800, -100);

                t_second.setFillColor(sf::Color::Green);
                t_second.setFont(arial);
                t_second.setOrigin(-500, -80);

                t_first.setFillColor(sf::Color::Green);
                t_first.setFont(arial);
                t_first.setOrigin(-200,-80);

                second.setFillColor(sf::Color::Green);
                second.setFont(arial);
                second.setOrigin(-500,-100);

                first.setFillColor(sf::Color::Green);
                first.setFont(arial);
                first.setOrigin(-200,-100);

                std::string t_r = "Result \n";
                std::string result = "";
                std::string t_n = "Enter second matrix \n";
                std::string t_s = "Enter the matrix \n";
                std::string second_m = "";
                std::string first_m = "\n";



                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    sf::RenderWindow window2(sf::VideoMode(1200, 500),"ADDITION!",
                                   sf::Style::Titlebar|sf::Style::Close);

                    int step = 0;
                    int _size = 0;
                    std::string result = "";


                    while(window2.isOpen())
                    {
                        double matrix1[9];
                        double matrix2[9];
                        t_first.setString(t_s);

                        sf::Event event;
                        while(window2.pollEvent(event))
                        {
                            if (step == 0) {
                                if (event.type == sf::Event::TextEntered) {
                                    if (event.text.unicode == 10){  // enter
                                        first_m += " ";
                                        first_m += static_cast<char>(event.text.unicode);
                                        _size += 1;
                                    }
                                    else if (event.text.unicode == 8) {  // backspace
                                        std::string pass;
                                        for(int i = 0; i < first_m.size() - 1; i++){
                                            pass += first_m[i];
                                        }
                                        first_m = pass;
                                        _size -= 1;
                                    }
                                    else if (event.text.unicode == 32) {
                                        first_m += static_cast<char>(event.text.unicode);
                                        _size += 1;// space
                                    }

                                    else if (event.text.unicode < 128) {
                                            //std::cout <<  << std::endl;
                                            first_m += static_cast<char>(event.text.unicode);
                                    }
                                }
                                if (_size == 9) {
                                    step = 1;
                                    t_second.setString(t_n);
                                    _size = -1;
                                }
                            }
                            if (step == 1){
                                if (event.type == sf::Event::TextEntered) {
                                    if (event.text.unicode == 10){  // enter
                                        second_m += " ";
                                        second_m += static_cast<char>(event.text.unicode);
                                        _size += 1;
                                    }
                                    else if (event.text.unicode == 8) {  // backspace
                                        std::string pass;
                                        for(int i = 0; i < second_m.size() - 1; i++){
                                            pass += second_m[i];
                                        }
                                        second_m = pass;
                                        _size -= 1;
                                    }
                                    else if (event.text.unicode == 32) {
                                        second_m += static_cast<char>(event.text.unicode);
                                        _size += 1;// space
                                    }

                                    else if (event.text.unicode < 128) {
                                        //std::cout <<  << std::endl;
                                        second_m += static_cast<char>(event.text.unicode);
                                    }
                                }
                                if (_size == 9){
                                    step = 2;
                                }
                            }
                            if (step == 2){

                                std::string str;
                                Transform_to_int(matrix1, first_m);
                                Transform_to_int(matrix2, second_m);
                                for(int i = 0; i < 9; i++){
                                    std::cout << matrix1[i] << " " << matrix2[i] << std::endl;
                                }
                                step = 3;
                             }
                            if (step == 3){

                                Vec33d First(matrix1);
                                std::cout << First;
                                Vec33d Second(matrix2);
                                std::cout << Second;

                                auto Result = First + Second;
                                std::cout << First << " " << Result << " " << Second <<std::endl;
                                result = Result.Transform_to_str(result);
                                std::cout << result << std::endl;
                                step = 4;
                            }
                            if (step == 4){
                                t_r += result;
                                title_result.setString(t_r);
                                std::cout << t_r << std::endl;
                                step = 5;
                            }


//
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {window2.close();step = 0;}
                            if(event.type == sf::Event::Closed) {window2.close(); step = 0;}
                        }
                        first.setString(first_m);
                        second.setString(second_m);


                        window2.clear(sf::Color::Black);
                        window2.draw(t_second);
                        window2.draw(t_first);
                        window2.draw(first);
                        window2.draw(second);
                        window2.draw(title_result);

                        window2.display();
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
                {
                    sf::RenderWindow window2(sf::VideoMode(1200, 500),"DIFFERENCE!");
                    int step = 0;
                    int _size = 0;
                    std::string result = "";


                    while(window2.isOpen())
                    {
                        double matrix1[9];
                        double matrix2[9];
                        t_first.setString(t_s);

                        sf::Event event;
                        while(window2.pollEvent(event))
                        {
                            if (step == 0) {
                                if (event.type == sf::Event::TextEntered) {
                                    if (event.text.unicode == 10){  // enter
                                        first_m += " ";
                                        first_m += static_cast<char>(event.text.unicode);
                                        _size += 1;
                                    }
                                    else if (event.text.unicode == 8) {  // backspace
                                        std::string pass;
                                        for(int i = 0; i < first_m.size() - 1; i++){
                                            pass += first_m[i];
                                        }
                                        first_m = pass;
                                        _size -= 1;
                                    }
                                    else if (event.text.unicode == 32) {
                                        first_m += static_cast<char>(event.text.unicode);
                                        _size += 1;// space
                                    }

                                    else if (event.text.unicode < 128) {
                                        //std::cout <<  << std::endl;
                                        first_m += static_cast<char>(event.text.unicode);
                                    }
                                }
                                if (_size == 9) {
                                    step = 1;
                                    t_second.setString(t_n);
                                    _size = -1;
                                }
                            }
                            if (step == 1){
                                if (event.type == sf::Event::TextEntered) {
                                    if (event.text.unicode == 10){  // enter
                                        second_m += " ";
                                        second_m += static_cast<char>(event.text.unicode);
                                        _size += 1;
                                    }
                                    else if (event.text.unicode == 8) {  // backspace
                                        std::string pass;
                                        for(int i = 0; i < second_m.size() - 1; i++){
                                            pass += second_m[i];
                                        }
                                        second_m = pass;
                                        _size -= 1;
                                    }
                                    else if (event.text.unicode == 32) {
                                        second_m += static_cast<char>(event.text.unicode);
                                        _size += 1;// space
                                    }

                                    else if (event.text.unicode < 128) {
                                        //std::cout <<  << std::endl;
                                        second_m += static_cast<char>(event.text.unicode);
                                    }
                                }
                                if (_size == 9){
                                    step = 2;
                                }
                            }
                            if (step == 2){

                                std::string str;
                                Transform_to_int(matrix1, first_m);
                                Transform_to_int(matrix2, second_m);
                                for(int i = 0; i < 9; i++){
                                    std::cout << matrix1[i] << " " << matrix2[i] << std::endl;
                                }
                                step = 3;
                            }
                            if (step == 3){

                                Vec33d First(matrix1);
                                std::cout << First;
                                Vec33d Second(matrix2);
                                std::cout << Second;

                                auto Result = First - Second;
                                std::cout << First << " " << Result << " " << Second <<std::endl;
                                result = Result.Transform_to_str(result);
                                std::cout << result << std::endl;
                                step = 4;
                            }
                            if (step == 4){
                                t_r += result;
                                title_result.setString(t_r);
                                std::cout << t_r << std::endl;
                                step = 5;
                            }


//
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {window2.close();step = 0;}
                            if(event.type == sf::Event::Closed) {window2.close();step = 0;}
                        }
                        first.setString(first_m);
                        second.setString(second_m);


                        window2.clear(sf::Color::Black);
                        window2.draw(t_second);
                        window2.draw(t_first);
                        window2.draw(first);
                        window2.draw(second);
                        window2.draw(title_result);

                        window2.display();
                    }
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                {
                    sf::RenderWindow window2(sf::VideoMode(1200, 500),"MULTIPLICATION!");

                    int step = 0;
                    int _size = 0;
                    std::string result = "";


                    while(window2.isOpen())
                    {
                        double matrix1[9];
                        double matrix2[9];
                        t_first.setString(t_s);

                        sf::Event event;
                        while(window2.pollEvent(event))
                        {
                            if (step == 0) {
                                if (event.type == sf::Event::TextEntered) {
                                    if (event.text.unicode == 10){  // enter
                                        first_m += " ";
                                        first_m += static_cast<char>(event.text.unicode);
                                        _size += 1;
                                    }
                                    else if (event.text.unicode == 8) {  // backspace
                                        std::string pass;
                                        for(int i = 0; i < first_m.size() - 1; i++){
                                            pass += first_m[i];
                                        }
                                        first_m = pass;
                                        _size -= 1;
                                    }
                                    else if (event.text.unicode == 32) {
                                        first_m += static_cast<char>(event.text.unicode);
                                        _size += 1;// space
                                    }

                                    else if (event.text.unicode < 128) {
                                        //std::cout <<  << std::endl;
                                        first_m += static_cast<char>(event.text.unicode);
                                    }
                                }
                                if (_size == 9) {
                                    step = 1;
                                    t_second.setString(t_n);
                                    _size = -1;
                                }
                            }
                            if (step == 1){
                                if (event.type == sf::Event::TextEntered) {
                                    if (event.text.unicode == 10){  // enter
                                        second_m += " ";
                                        second_m += static_cast<char>(event.text.unicode);
                                        _size += 1;
                                    }
                                    else if (event.text.unicode == 8) {  // backspace
                                        std::string pass;
                                        for(int i = 0; i < second_m.size() - 1; i++){
                                            pass += second_m[i];
                                        }
                                        second_m = pass;
                                        _size -= 1;
                                    }
                                    else if (event.text.unicode == 32) {
                                        second_m += static_cast<char>(event.text.unicode);
                                        _size += 1;// space
                                    }

                                    else if (event.text.unicode < 128) {
                                        //std::cout <<  << std::endl;
                                        second_m += static_cast<char>(event.text.unicode);
                                    }
                                }
                                if (_size == 9){
                                    step = 2;
                                }
                            }
                            if (step == 2){

                                std::string str;
                                Transform_to_int(matrix1, first_m);
                                Transform_to_int(matrix2, second_m);
                                for(int i = 0; i < 9; i++){
                                    std::cout << matrix1[i] << " " << matrix2[i] << std::endl;
                                }
                                step = 3;
                            }
                            if (step == 3){

                                Vec33d First(matrix1);
                                std::cout << First;
                                Vec33d Second(matrix2);
                                std::cout << Second;

                                auto Result = First * Second;
                                std::cout << First << " " << Result << " " << Second <<std::endl;
                                result = Result.Transform_to_str(result);
                                std::cout << result << std::endl;
                                step = 4;
                            }
                            if (step == 4){
                                t_r += result;
                                title_result.setString(t_r);
                                std::cout << t_r << std::endl;
                                step = 5;
                            }


//
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {window2.close(); step = 0;}
                            if(event.type == sf::Event::Closed) {window2.close(); step = 0;}
                        }
                        first.setString(first_m);
                        second.setString(second_m);


                        window2.clear(sf::Color::Black);
                        window2.draw(t_second);
                        window2.draw(t_first);
                        window2.draw(first);
                        window2.draw(second);
                        window2.draw(title_result);

                        window2.display();
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    sf::RenderWindow window2(sf::VideoMode(1200, 500),"RESERVE!");
                    int step = 0;
                    int _size = 0;
                    std::string result = "";

                    while(window2.isOpen())
                    {
                        double matrix1[9];

                        sf::Event event;
                        while(window2.pollEvent(event)) {
                            if (step == 0) {
                                if (event.type == sf::Event::TextEntered) {
                                    if (event.text.unicode == 10) {  // enter
                                        first_m += " ";
                                        first_m += static_cast<char>(event.text.unicode);
                                        _size += 1;
                                    } else if (event.text.unicode == 8) {  // backspace
                                        std::string pass;
                                        for (int i = 0; i < first_m.size() - 1; i++) {
                                            pass += first_m[i];
                                        }
                                        first_m = pass;
                                        _size -= 1;
                                    } else if (event.text.unicode == 32) {
                                        first_m += static_cast<char>(event.text.unicode);
                                        _size += 1;// space
                                    } else if (event.text.unicode < 128) {
                                        //std::cout <<  << std::endl;
                                        first_m += static_cast<char>(event.text.unicode);
                                    }
                                }
                                if (_size == 9) {
                                    step = 1;
                                    title_result.setString(t_r);
                                    _size = -1;
                                }
                            }
                            if (step == 1) {
                                std::string str;
                                Transform_to_int(matrix1, first_m);
                                step = 2;
                            }
                            if (step == 2) {
                                Vec33d First(matrix1);
                                auto Result = First.Inverse();
                                result = Result.Transform_to_str(result);
                                step = 3;
                            }
                            if (step == 3) {
                                t_r += result;
                                title_result.setString(t_r);
                                title_result.setOrigin(-600, -80);
                                std::cout << t_r << std::endl;
                                step = 4;
                            }
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){window2.close();step = 0;}
                            if(event.type == sf::Event::Closed) {window.close();step = 0;}
                           }

                        t_first.setString(t_s);
                        first.setString(first_m);


                        window2.clear(sf::Color::Black);
                        window2.draw(t_first);
                        window2.draw(first);
                        window2.draw(title_result);

                        window2.display();
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                {
                    sf::RenderWindow window2(sf::VideoMode(1200, 500),"TRANSPOSED!");
                    int step = 0;
                    int _size = 0;
                    std::string result = "";

                    while(window2.isOpen())
                    {
                        double matrix1[9];

                        sf::Event event;
                        while(window2.pollEvent(event)) {
                            if (step == 0) {
                                if (event.type == sf::Event::TextEntered) {
                                    if (event.text.unicode == 10) {  // enter
                                        first_m += " ";
                                        first_m += static_cast<char>(event.text.unicode);
                                        _size += 1;
                                    } else if (event.text.unicode == 8) {  // backspace
                                        std::string pass;
                                        for (int i = 0; i < first_m.size() - 1; i++) {
                                            pass += first_m[i];
                                        }
                                        first_m = pass;
                                        _size -= 1;
                                    } else if (event.text.unicode == 32) {
                                        first_m += static_cast<char>(event.text.unicode);
                                        _size += 1;// space
                                    } else if (event.text.unicode < 128) {
                                        //std::cout <<  << std::endl;
                                        first_m += static_cast<char>(event.text.unicode);
                                    }
                                }
                                if (_size == 9) {
                                    step = 1;
                                    title_result.setString(t_r);
                                    _size = -1;
                                }
                            }
                            if (step == 1) {
                                std::string str;
                                Transform_to_int(matrix1, first_m);
                                step = 2;
                            }
                            if (step == 2) {
                                Vec33d First(matrix1);
                                auto Result = First.Transposed();
                                result = Result.Transform_to_str(result);
                                step = 3;
                            }
                            if (step == 3) {
                                t_r += result;
                                title_result.setString(t_r);
                                title_result.setOrigin(-600, -80);
                                std::cout << t_r << std::endl;
                                step = 4;
                            }
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){window2.close();step = 0;}
                            if(event.type == sf::Event::Closed) {window.close();step = 0;}
                        }

                        t_first.setString(t_s);
                        first.setString(first_m);


                        window2.clear(sf::Color::Black);
                        window2.draw(t_first);
                        window2.draw(first);
                        window2.draw(title_result);

                        window2.display();
                    }
                }
            }
            window.clear();
            window.draw(sprite);

            window.draw(description);
            description.setString(std::string("Choose 1 of variant for work with matrix!"));


            window.draw(addition);
            addition.setString(std::string("Summ of matrix \n "
                                           "button  -  <A> "));
            window.draw(difference);
            difference.setString(std::string("Difference of matrix \n"
                                           "button  -  <B>"));
            window.draw(multiplication);
            multiplication.setString(std::string("Multiplication of matrix \n"
                                                 "button  -  <C>"));
            window.draw(reverse);
            reverse.setString(std::string("Reverse of matrix \n"
                                                 "button  -  <D>"));
            window.draw(transposed);
            transposed.setString(std::string("Transposed of matrix \n"
                                                 "button  -  <F>"));



            window.display();

        }
        return 0;
}