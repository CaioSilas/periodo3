
package com.mycompany.tp2;
import java.util.ArrayList;


/**
 *
 * @author silas
 */
public class Livro {
    private ArrayList <String> escritores = new <String>ArrayList();
    private String titulo;
    private ArrayList <String> capitulos = new <String>ArrayList();
    private int anoPublicacao;
    private String idiomaOriginal;
    private ArrayList <String> keywords = new <String>ArrayList();
   
    
    public Livro(ArrayList escritores,String titulo, ArrayList capitulos, int anoPublicacao, String idiomaOriginal, ArrayList keywords){
        this.escritores = escritores;
        this.capitulos = capitulos;
        this.titulo = titulo;
        this.anoPublicacao = anoPublicacao;
        this.idiomaOriginal = idiomaOriginal;
        this.keywords = keywords;
    }
    
    
    public ArrayList<String> getEscritores() {
        return escritores;
    }

    public void setEscritores(ArrayList<String> escritores) {
        this.escritores = escritores;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public ArrayList<String> getCapitulos() {
        return capitulos;
    }

    public void setCapitulos(ArrayList<String> capitulos) {
        this.capitulos = capitulos;
    }

    public int getAnoPublicacao() {
        return anoPublicacao;
    }

    public void setAnoPublicacao(int anoPublicacao) {
        this.anoPublicacao = anoPublicacao;
    }

    public String getIdiomaOriginal() {
        return idiomaOriginal;
    }

    public void setIdiomaOriginal(String idiomaOriginal) {
        this.idiomaOriginal = idiomaOriginal;
    }

    public ArrayList<String> getKeywords() {
        return keywords;
    }

    public void setKeywords(ArrayList<String> keywords) {
        this.keywords = keywords;
    }
    
}
