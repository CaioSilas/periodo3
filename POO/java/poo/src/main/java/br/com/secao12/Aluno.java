
package br.com.secao12;

/**
 *
 * @author silas
 */


//herdando de Pessoa nome e ano_nascimento
public class Aluno extends Pessoa {
    private String ra;
    
    //fazendo o usuario ja inicar o aluno com informações
    public Aluno(String nome, int ano_nascimento, String ra){
        //passando Pessoa(nome,ano_nascimento)
        super (nome,ano_nascimento);
        this.ra= ra;
    }
    
    
    
    public String getRa(){
        return this.ra;
    }
    public void setRa(String ra){
        this.ra = ra;
    }
    
    @Override
    public String toString(){
        return super.toString() + "\nR.A: " + this.ra;
    }
}
