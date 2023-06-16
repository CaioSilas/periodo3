
package br.com.secao12;

/**
 *
 * @author silas
 */
public class Professor extends Pessoa {
       private String matricula;
       
       public Professor(String nome, int ano, String matricula){
           super(nome,ano);
           this.matricula = matricula;
       }
       
       public String getMatricula(){
           return this.matricula;
       }
       
       public void setMatricula(String mat){
           this.matricula = mat;
       }
       
       public String toString(){
           return super.toString() + "\nmatricula: " + this.matricula;
       }
}
