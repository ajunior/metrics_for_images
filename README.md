
### Forma de usar

 
 Instale as libs necessárias com o comando no terminal Linux:


    sudo apt-get install build-essential
    sudo apt-get install libopencv-dev
    sudo apt-get install make
    
 Compile o código:

    make clean; make

Configure e execute o programa:

- Dentro da pasta input crie um arquivo (lista_referencia) e nele liste todos os nomes dos arquivos das imagens de referências, repíta o processo para as imagens novas (lista_avaliada).
- Adicione as novas imagens e as imagens de referência dentro da pasta imput.
- Execute o programa com o seguinte comando:

    ./bin/main input/lista_referencia input/lista_avaliada


Os resultados serão gravados automaticamente dentro das pastas results em arquivos txt.