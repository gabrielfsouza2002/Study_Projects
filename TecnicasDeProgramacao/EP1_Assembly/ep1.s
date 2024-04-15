section .text

funcao_eh_primo:                
    CMP r12, 1                ;if(n==1) -> não é primo
    JE entao_nao_eh_primo       
    MOV rax, 2                ;rax = divisor
    MOV r8, rax               ;r8 = auxiliar para multiplicar o quadrado do divisor

     while1:                  ;while(div*div<=n && eh_primo) 
        MUL r8                ;rax = div*div
        CMP rax, r12            
        JG entao_eh_primo     ;caso div*div > n saimos do laço e o numero é primo
        MOV rax, r12          ;rax atualiza para n      
        MOV r9, r8            ;r9 salva r8(div) pois r8 vai receber outro valor nas linhas abaixo
        DIV r9                ;rax = r12(n)/r9(div)    
        OR rdx, rdx           ;if (n%div==0) -> não eh_primo
        JE entao_nao_eh_primo   
        MOV rax, r8           ;else -> rax = r8(div)+1 e r8 = rax
        INC eax
        MOV r8, rax
        JMP while1       

    entao_eh_primo:           ;rcx = flag (0 ou 1)
        MOV rcx, 1
        ret

    entao_nao_eh_primo:   
        MOV rcx,0
        ret

funcao_proximo_primo:   
    INC r12                   ;pncrementa 1 ao numero r12(n) para driblar o caso de n ser primo e não entrar no laço
    call funcao_eh_primo      ;por força bruta verificamos o proximo numero até que ele seja primo
    CMP rcx, 1                ;rcx é a flag que indica se o número é primo ou não.
    JE imprime_se_0           ;while(!primo(r12)) -> r12++
    JMP funcao_proximo_primo

funcao_mult_2_primos:
    MOV r9, 1             ;fator
    MOV rcx, 0            ;cont
    MOV r10,r12           ;como r12 (n) vai ser alterado (decomposto), guardamos seu valor em r10.

    while3:
        MOV rdx, 0        ;zeramos o rdx para não dar problema no rax na divisção do laço
        INC r9            ;fator começa com valor = 2 e vai incrimentando 1 no laço
        MOV rax,r12       ;divindo o que esta no r12 (n) por r9 (fator)
        DIV r9              
        OR rdx, rdx       ;se o resto da divisãp é 0 -> if1. Se no if1 o rcx (cont) for diferente de zero -> if2
        JE if1
        JE if2          
        CMP r12, 1        ;while3(n >1) 
        JG while3         ;fazemos o laço até que r12(n) seja <= 1 
        JLE criterios    ;Ao sair do laço, pulamos para o critério
        if1:              ;if(n%fator == 0 && cont =0) -> mult1 = r14
            CMP rcx, 0    ;Condição pra verificar se o caso do if2
            JNE if2         
            INC rcx       ;Atualizando o contador
            MOV rax, r12  ;dividir o r12(n) por r9(fator)
            DIV r9          
            MOV r12,rax   ;atulaliza o r12 n = n/fator
            MOV r14, r9   ;r14 irá salvar o primeiro multiplo primo
            JMP while3

        if2:              ;if(cont!=0 && n%fator ==0) -> r15 = mult2
            CMP rcx, 0      
            JE while3
            INC rcx       ;atualizamos rcx para fazer a verificação se o numero pode ou não ser produto de dois primos no rotulo critério 
            MOV r15, r9   ;r15 irá salvar o segundo multiplo primo
            JMP criterios

    criterios:            ;if(cont = 2 && mult1*mult2 == r10) -> é produto de dois primos e podemos imprimir
        CMP rcx, 2          
        JNE fim           ;else -> acabamos o programa
        MOV rax, r14        
        MUL r15
        CMP rax, r10      ;r10 = n inicial
        JNE fim
        JMP imprime_se_1      


scanf:  ;leitura da entrada
    MOV rdi, 0       
    MOV rsi, input  
    MOV rdx, 15
    MOV rax, 0          
    syscall 
      
    prepara_input:
        MOV rcx, 1                    ;rcx vai guardar a posição do vetor
        MOV r11, 3                    ;r11 vai guardar o numero de vezes que percorri o vetor
        MOV r13, rax                  ;r13 = rax(tamanho da entrada)

    input_numero:                     ;Conversão de ascii para decimal
        INC rcx                       ;rcx começa como 2
        INC r11                       ;r11 começa como 4
        MOV bl, [input+rcx]           ;neste rotulo leremos o vetor a partir da posição 2 (desconsidera o comando e o espaço)
        SUB bl, ASCII                 ;conversão
        MOV rax, r13                  ;rax = tamanho da entrada
        CMP r11, rax                  ;se o numero de vezes que eu percorri o vetor é igual ao tamanho do vetor, então vou para o processo final do input
        JE final_do_input
        MOV r8, rax                   ;r8 = tamanho da entrada
        SUB r8, r11                   ;r8 = r8 - n vezes que percorri meu vetor
        MOV al ,bl                    ;al = bl(digito da posição rcx)
        MOV r10, 10                     

        while_potencias_de_10:        ;while(r8 != 0)-> multiplica o digito por 10
            MUL r10                   ;rax(al) = rax*10   
            DEC r8                      
            CMP r8, 0                   
            JE soma_digitos_potencia
            JMP while_potencias_de_10
        
        soma_digitos_potencia:        ;junta todos os digitos
            ADD r12,rax               ;r12 = numeros em potencias de 10
            JMP input_numero

    final_do_input:
        ADD r12,rbx                   ;adiciona o ultimo digito
        MOV bl, [input]               ;armazena o comando(0 ou 1) no bl
        SUB bl, 48                    ;conversão
        MOV dl, bl                    ;dl = bl
        ret


imprime_se_0:
MOV rcx, 0                            ;zerar o apontador de digitos rcx

    conta_digitos_se_0:
        MOV rdx, 0                    ;zerar rdx para não ocorrer problemas no durante o laço
        MOV bl, 10                             
        DIV rbx                       ;divide rax por 10 
        INC rcx                         
        CMP rax,0                     ;se o quociente da divisão != 0 -> continuamos contando os digitos
        JNE conta_digitos_se_0          
        MOV bl,10                       
        MOV [output0+rcx],bl          ;preenche a a posição 1 com o caracter 'space'                    
        MOV rax, r12                  ;r12 = numero digitado
    insere_out_0:
        MOV rdx, 0                    ;zerar rdx para não ocorrer problemas no durante o laço
        MOV bl, 10                    ;divide rax por 10     
        DIV rbx                       ;rax = quociente    
        MOV bl, dl                    ;colocando o numero da direita para esquerda no output0
        ADD bl, ASCII                 ;conversão
        DEC rcx
        MOV [output0+rcx],bl
        CMP rax, 0
        JNE insere_out_0
        
    print_syscall_0: 
        MOV rdi, 1  
        MOV rsi, output0         
        MOV rdx, 15        
        MOV rax, 1           
        syscall    
        JMP fim

imprime_se_1:
MOV rcx, 0
MOV rax, r14                              ;rax = r14(primeiro multiplo)

    conta_digitos_se_1_part1:             ;imprime o primeiro multiplo
        MOV rdx, 0                        ;zerar o apontador de digitos rcx
        MOV bl, 10                                         
        DIV rbx                           ;divide rax por 10 
        INC rcx
        CMP rax,0                         ;se o quociente da divisão != 0 -> continuamos contando os digitos
        JNE conta_digitos_se_1_part1
        MOV r8, rcx
        MOV bl, 32                          
        MOV [output1+rcx],bl              ;preenche a a posição rcx com o caracter de quebra de linha             
        MOV rax, r14                       

    insere_out_1_part1: 
        MOV rdx, 0                            ;zerar o apontador de digitos rcx                         
        MOV bl, 10                                              
        DIV rbx                               ;divide rax por 10 
        MOV bl, dl                              
        ADD bl, ASCII                         ;conversão
        DEC rcx
        MOV [output1+rcx],bl                  ;colocando o numero da direita para esquerda no output0
        CMP rax, 0
        JNE insere_out_1_part1
    
    conta_digitos_se_1_part2:     ;codigo análogo ao da part 1 porém com a imprissão do segundo multipplo
        MOV rax, r15              ;r15 = segundo multiplo
        loop:
        MOV rdx, 0
        MOV bl, 10
        DIV rbx
        INC rcx
        CMP rax,0
        JNE loop           
        MOV rax, r15    
        ADD rcx, r8
        INC rcx

    insere_out_1_part2:
        MOV rdx, 0
        MOV bl, 10
        DIV rbx
        MOV bl, dl
        ADD bl, ASCII           
        MOV [output1+rcx],bl  ;colocando o numero da direita para esquerda no output1             
        DEC rcx
        CMP rax, 0
        JNE insere_out_1_part2  
        INC rcx                   
        ADD rcx,r8
        MOV bl, 10
        MOV [output1+rcx],bl  ;preenche a a posição rcx com o caracter 'space'
    print_syscall_1: 
        MOV rdi, 1  
        MOV rsi, output1         
        MOV rdx, 15        
        MOV rax, 1           
        syscall    
        JMP fim         

    
global _start   
_start: 
    call scanf
    OR bl, bl                 ;if o comando bl(scanf) == 0 -> funcao_proximo_primo
    JE funcao_proximo_primo                               ;else -> func_mult_2_primos
    CMP bl, 1
    JE funcao_mult_2_primos



fim: 
    MOV rdi, 0          
    MOV rax, 60          
    syscall   



section .data
ASCII:  equ 48

section .bss
input: resb 15
output0: resb 15
output1: resb 15

