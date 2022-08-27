// autoria de Luiz Maurício do Valle Pereira
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <list>
#include <queue>

using namespace std;

bool verify(fstream &file) {
    // função que verifica o arquivo xml
    stack<std::string> stack;
    
    bool error = false;
    if (file.is_open()) {
        string line = "";
        // pegando as linhas do arquivo
        while(getline(file, line)) {
            // for que percorre a linha char por char
            for (int i = 0; i< line.size(); i++) {
                if (line[i] == '<') {
                    bool desempilha = false;
                    if (line[i+1] == '/') {
                        i++;  // pulando o index da barra
                        desempilha = true;
                    }
                    string tag ="";
                    // percorre a linha dentro da tag até achar o fechamento
                    for (int j = i+1; j<line.size(); j++) {
                        if (line[j] == '>' && desempilha) {
                            if (!stack.empty()) {
                                if (stack.top().compare(tag) == 0) {
                                    // checando se tem uma tag igual no topo
                                    //cout << "pop: " << tag << endl;
                                    stack.pop();
                                } else {
                                    error = true;
                                }
                            } else {
                                error = true;
                            }
                            break;
                        } else if (line[j] == '>' && !desempilha) {
                            stack.push(tag);
                            break;
                        }
                        tag = tag + line[j];
                    }
                }
            }
        }
    }
    if (!stack.empty()) {
        // alguma tag não foi fechada
        error = true;
    }
    file.close();
    return error;
}

void get_nome(fstream& file, list<string>& lista_nomes){
    // pega a string entre as tags <name>
    if (file.is_open()) {
        string line = "";
        string name = "";
        while(getline(file,line)) {
            name = "";
            while (line.find("<name>") != line.npos) {
                int pos = static_cast<int>(line.find("<name>"));
                for (int i = pos+6; i < line.size(); i++) {  // 6 é o tamanho da string <name>
                    if (line[i] == '<') {
                         line[pos+1] = ' ';
                         break;
                    } else {
                        name = name + line[i];
                    }
                }
            }
            if (name != "") {
                lista_nomes.push_back(name);
            }
        }
    }
    file.close();
};

void get_altura(fstream& file, list<string>& lista_altura) {
    // pega a altura de cada matriz
    if (file.is_open()) {
        string line = "";
        while(getline(file,line)) {
            string height = "";
            while (line.find("<height>") != line.npos) {
                int pos = static_cast<int>(line.find("<height>"));
                for (int i = pos+8; i < line.size(); i++) {  // 6 é o tamanho da string <name>
                    if (line[i] == '<') {
                        line[pos+1] = ' ';
                        break;
                    } else {
                        height = height + line[i];
                    }
                }
            }
            if (height != "") {
                lista_altura.push_back(height);
            }
        }
    }
    file.close();
}

void get_largura(fstream& file, list<string>& lista_largura) {
    // pega a largura de cada matriz
    if (file.is_open()) {
        string line = "";
        while(getline(file,line)) {
            string width = "";
            while (line.find("<width>") != line.npos) {
                int pos = static_cast<int>(line.find("<width>"));
                for (int i = pos+7; i < line.size(); i++) {  // 6 é o tamanho da string <name>
                    if (line[i] == '<') {
                        line[pos+1] = ' ';
                        break;
                    } else {
                        width = width + line[i];
                    }
                }
            }
            if (width != "") {
                lista_largura.push_back(width);
            }
        }
    }
    file.close();
}

void get_matriz(fstream& file, list<string>& lista_matriz, list<string>& lista_altura) {
    // pega a matriz entre as tagas <data>
    list<string> matrizes;
    
    // colocando todas as linhas em uma lista auxiliar
    if (file.is_open()) {
        string line;
        while(getline(file,line)) {
            if (line.find('<') == line.npos && line != "") {
                matrizes.push_back(line);
                std::cout << line << endl;  // se eu retirar essa linha o program não avalia
            }
        }
    }
    
    
    // separando a lista em matrizes na lista_matriz
    for (int i = 0; i < lista_altura.size(); i++) {
        string emp = "";
        int tam = stoi(lista_altura.front());
        for (int j = 0; j < tam; j++) {
            emp = emp + matrizes.front();
            matrizes.pop_front();
        }
        lista_matriz.push_back(emp);
        lista_altura.pop_front();
    }
    
    file.close();
}

int processar(string height, string width, string matriz) {
    int altura = stoi(height);
    int largura = stoi(width);
    
    char m_aux[altura][largura];
    char m_ref[altura][largura];
    
    int k = 0;
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            // para ter certeza de que cada posição é checada apenas uma vez
            m_aux[i][j] = '0';
            m_ref[i][j] = matriz[k];
            k++;
        }
    }
    
    int num = 0;
    queue<int>fila_row;
    queue<int>fila_column;
    
    for (int i = 0; i != altura; i++) {
        for (int j = 0; j!= altura; j++){
            // buscando figuras na imagem
            if (m_aux[i][j] == '0' && m_ref[i][j]=='1') {
                // figura encontrada
                fila_row.push(i);
                fila_column.push(j);
                
                while(!fila_row.empty()) {
                    //cout << "passando" << endl;
                    // procesando uma figura por vez
                    int temp_row = fila_row.front();
                    int temp_column = fila_column.front();
                    fila_row.pop();
                    fila_column.pop();
                    
                    if (temp_row-1 >= 0) {
                        if (m_ref[temp_row-1][temp_column] == '1' && m_aux[temp_row-1][temp_column] == '0') {
                            // checando sul
                            fila_row.push(temp_row-1);
                            fila_column.push(temp_column);
                            m_aux[temp_row-1][temp_column] = '1';
                        }
                    }
                    if (temp_row + 1 <= altura) {
                        if (m_ref[temp_row+1][temp_column] == '1' && m_aux[temp_row+1][temp_column] == '0') {
                            // checando norte
                            fila_row.push(temp_row+1);
                            fila_column.push(temp_column);
                            m_aux[temp_row+1][temp_column] = '1';
                        }
                    }
                    if (temp_column + 1 <= largura) {
                        if (m_ref[temp_row][temp_column+1] == '1' && m_aux[temp_row][temp_column+1] == '0') {
                            // checando leste
                            fila_row.push(temp_row);
                            fila_column.push(temp_column+1);
                            m_aux[temp_row][temp_column+1] = '1';
                        }
                    }
                    if (temp_column - 1 >= 0) {
                        if (m_ref[temp_row][temp_column-1] == '1' && m_aux[temp_row][temp_column-1] == '0') {
                            // checando oeste
                            fila_row.push(temp_row);
                            fila_column.push(temp_column-1);
                            m_aux[temp_row][temp_column-1] = '1';
                        }
                    }
                    m_aux[temp_row][temp_column] = '1';
                }
            num++;
            }
        }
    }
    return num;
}

int main() {

    string xmlfilename;

    std::cin >> xmlfilename;  // entrada
    
    std::fstream file(xmlfilename);
    
    if (verify(file) == true) {
        cout << "error" << endl;
        return 0;
    }
    
    // lista que contém nomes de imagens
    list<string> lista_nomes;
    list<string> lista_altura;
    list<string> lista_largura;
    list<string> lista_matriz;
    
    file.open(xmlfilename);
    get_nome(file, lista_nomes);
    
    file.open(xmlfilename);
    get_altura(file, lista_altura);
    
    file.open(xmlfilename);
    get_largura(file, lista_largura);
    
    file.open(xmlfilename);
    get_matriz(file, lista_matriz, lista_altura);
    
    //prints finais
    int tam = lista_nomes.size();
    for (int i = 0; i < tam; i++) {
        cout << lista_nomes.front() << " " << processar(lista_altura.front(), lista_largura.front(), lista_matriz.front()) << endl;
        lista_nomes.pop_front();
        lista_altura.pop_front();
        lista_largura.pop_front();
        lista_matriz.pop_front();
    }
    
    return 0;
    // abrindo arquivo
    // std::ifstream f(xmlfilename);    achei outra solução melhor
    /*
    structures::LinkedList<string> pilha_tag{};
    
    char ch;
    
    
    char tag[20];  // guarda a tag
    char *begin = tag;  // usado no fill
    char *end = begin + sizeof(tag);  // usado no fill
    
    bool tag_write = false;  // abilita escrita em tag
    bool closing_tag = false;  // mostra que é uma closing tag, não uma opening
    bool erro_tag = false;  // se tiver erro nas tags
    int i = 0;
    
    fstream fin(xmlfilename, fstream::in);
    
    /*
    while (fin >> noskipws >> ch && erro_tag == false) {
        cout << ch; // apenas para teste.
        if (ch == '<') {
            // abertura comum para qualquer tag
            tag_write = true;
            i = 0;
        } else if (ch == '>' && closing_tag == true) {
            // logica para dar pop na pilha
            if (!pilha_tag.empty() && pilha_tag.at(0) == tag) {
                //cout << '-' << tag << endl;
                pilha_tag.pop_front();
            } else {
                // printa error e sai do loop
                //cout << '/' << tag << endl;
                cout << "error" << endl;
                erro_tag = true;
            }
            // esvaziando o array tag após o uso
            std::fill(begin, end, 0);
            // caso seja o fechamento de uma closing tag
            i = 0;
            tag_write = false;
            closing_tag = false;
        } else if (ch == '>' && closing_tag == false) {
            if (!pilha_tag.empty() && tag == pilha_tag.at(0)) {
                cout << '=' << tag << endl;
                cout << "error" << endl;
                erro_tag = true;
            } else {
                // lógica para colocar na pilha
                cout << '+' << tag << endl;
                pilha_tag.push_front(tag);
            }
            //cout << '+' << tag << endl;
            pilha_tag.push_front(tag);
            // esvaziando o array tag após o uso
            std::fill(begin, end, 0);
            // caso seja o fechamento de uma tag normal
            i = 0;
            tag_write = false;
        } else if (tag_write == true && ch == '/') {
            // primeiro char de uma closing tag;
            closing_tag = true;
            i = 0;
        } else if (tag_write == true && ch != '/') {
            // escrevendo o nome da tag comum para qualquer tag
            tag[i] = ch;
            i++;
        }
    }
    
    // versão 2 do código
    
    split_return valores;  // valores de retorno da função split
    string line = "";  // saída da função getline
    int length = 0;
    int splits = 0;
    bool tag_error = false;
    
    while(std::getline(fin, line)) {
        //std::cout << "line:" << line << std::endl;
        split(line, '<', '>', valores);
        int j = 0;
        //cout << valores.currIndex << endl;
        for (int i = 1; i < valores.currIndex-1; i++) {
            //std::cout << strings[i] << endl;
            //cout << "string " << i << ": " << strings[i] << endl;
            //cout << "j: " << j << endl;
            //cout << "valores.open_indexes[j]: " << valores.open_indexes[j] << endl;
            if (i == valores.open_indexes[j] +1 && strings[i][0] != '/') {
                //cout << "push: " << strings[i] << endl;
                pilha_tag.push_front(strings[i]);
                j++;
            } else if (i == valores.open_indexes[j] +1 && strings[i][0] == '/') {
                pilha_tag.pop_front();
                //cout << "pop: " << pilha_tag.pop_front() << endl;
                //pilha_tag.pop_front();
                j++;
            }
        }
    }
    if (tag_error == false) {
        cout << "success" << endl;
    }
    
    // falta lógica para checar se a pilha está vazia no fim do programa
    
    // std::cout << xmlfilename << std::endl;  // esta linha deve ser removida
    file.close();
    */
}
