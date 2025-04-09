package TP2;

import java.io.*;
import java.util.*;

public class LerArquivo {
    /*
     * Versão feita no lab dia 08/04
     */

    public static void main(String[] args) throws FileNotFoundException {

        File file = new File("C:\\Users\\1429338\\Downloads\\AEDS-II-Puc-Minas-main\\TP2\\tmp\\disneyplus.csv");

        Scanner sc = new Scanner(file);

        Show saida = new Show(); 
        String linha = sc.nextLine();

        while (sc.hasNext()) {

            linha = sc.nextLine();
            saida.ler(linha); 

        }

        sc.close();

    }

}

class Show {

    // Atributos da classe
    private String show_id;
    private String type;
    private String title;
    private String director;
    private String[] cast;
    private String country;
    private String date;
    private String release_year;
    private String rating;
    private String duration;
    private String[] listed_in;

    // Construtor 1
    public Show() {
        this.show_id = "NaN";
        this.type = "NaN";
        this.title = "NaN";
        this.director = "NaN";
        this.country = "NaN";
        this.date = "NaN";
        this.release_year = "NaN";
        this.rating = "NaN";
        this.duration = "NaN";
    }

    // Construtor 2
    public Show(String show_id, String type, String title,
            String director, String cast[], String country,
            String date, String release_year, String rating,
            String duration, String listed_in[]) {

        this.show_id = show_id;
        this.type = type;
        this.title = title;
        this.director = director;
        this.country = country;
        this.date = date;
        this.release_year = release_year;
        this.rating = rating;
        this.duration = duration;
    }

    // Gets and sets

    public String getShow_id() {
        return show_id;
    }

    public void setShow_id(String show_id) {
        this.show_id = show_id;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDirector() {
        return director;
    }

    public void setDirector(String director) {
        this.director = director;
    }

    public String[] getCast() {
        return cast;
    }

    public void setCast(String[] cast) {
        this.cast = cast;
    }

    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getRelease_year() {
        return release_year;
    }

    public void setRelease_year(String release_year) {
        this.release_year = release_year;
    }

    public String getRating() {
        return rating;
    }

    public void setRating(String rating) {
        this.rating = rating;
    }

    public String getDuration() {
        return duration;
    }

    public void setDuration(String duration) {
        this.duration = duration;
    }

    public String[] getListed_in() {
        return listed_in;
    }

    public void setListed_in(String[] listed_in) {
        this.listed_in = listed_in;
    }

    public Show clone(Show entrada) {

        Show clone = new Show();
        clone.show_id = entrada.show_id;
        clone.type = entrada.type;
        clone.title = entrada.title;
        clone.director = entrada.director;
        clone.country = entrada.country;
        clone.date = entrada.date;
        clone.release_year = entrada.release_year;
        clone.rating = entrada.rating;
        clone.duration = entrada.duration;

        return clone;

    }

    public void imprimir(Show entrada) {

    }

    public Show ler(String entrada) {

        Show show = new Show();
        String[] leituraShow = new String[100];
        int i = 0, j = 0;
        System.out.println(entrada);

        if (entrada.charAt(i) != '"') {
            while (entrada.charAt(i) != ',') {
                leituraShow[j] += entrada.charAt(i);
                i++;
            }

            i++; 
            j++;
         
        }

        if (entrada.charAt(i) != ',' && entrada.charAt(i) == '"') {
            
            i++; 

            while (entrada.charAt(i) != '"') {
                leituraShow[j] += entrada.charAt(i);
                i++;
            }

            j++;
           
        }

        for(int k = 0; k < leituraShow.length; k++)
        {
            System.out.print(leituraShow[k] + ", ");
        }

        System.out.println();
        return show;
    }

}