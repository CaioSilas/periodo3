package com.mycompany.poo;

public class programa24 {
    public static void main(String[] args) {
        Pessoa pessoal = new Pessoa();

        pessoal.nome = "caio silas";
        pessoal.email = "caio.silas@gmail.com";
        pessoal.ano_nascimento = 2000;

        System.out.println("nome: " + pessoal.nome);
        System.out.println("email: " + pessoal.email);
        System.out.println("ano de nacimento: " + pessoal.ano_nascimento);
    }
}
