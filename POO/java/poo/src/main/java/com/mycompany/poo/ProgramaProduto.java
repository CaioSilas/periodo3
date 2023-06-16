package com.mycompany.poo;


public class ProgramaProduto {

	public static void main(String[] args) {
		
		Produto p1 = new Produto();
		
		p1.set_nome("baladegoma");
		p1.set_preco(45);
		System.out.println(p1.preco);
		p1.set_desconto(20);
		
		
		System.out.println(p1.precototal()+ "\n" + p1.nome);
		
	}

}
