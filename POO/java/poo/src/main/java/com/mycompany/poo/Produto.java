package com.mycompany.poo;




public class Produto {
	String nome;
	float preco;
	float desconto;
	
	
	void aumentar_preco() {
		this.preco = this.preco + 10;
	}
	
	void set_preco(float preco) {
		this.preco = preco;
	}
	void set_nome(String nome) {
		this.nome = nome;
	}
	void set_desconto(float desconto) {
		this.desconto = desconto;
	}
	
	float get_desconto() {
		return this.desconto;
	}
	float get_preco() {
		return this.preco;
	}
	
	float precototal() {
		float total = (this.get_preco() * this.get_desconto()) / 100;
		total = this.get_preco() - total;
		return total;
	}
}

