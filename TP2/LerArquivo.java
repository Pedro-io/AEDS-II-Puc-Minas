package TP2;

import java.util.*;
import java.io.*;

public class LerArquivo {

    public static void main(String[] args) throws FileNotFoundException {

        File file = new File("/home/1429338/Aulas/AEDS-II-Puc-Minas/TP2/tmp/disneyplus.csv");

        Scanner sc = new Scanner(file);

        String linha = sc.nextLine();

        while (sc.hasNext()) {

            System.out.println(linha);

            linha = sc.nextLine();

        }

        sc.close();

    }

}

class Show {

    private String show_id;
    private String type;
    private String title;
    private String director;
    private String cast[];
    private String country;
    private String date;
    private String release_year;
    private String rating;
    private String duration;
    private String listed_in[];

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
   public Show(String release_year){

    this.release_year = release_year; 
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

   



   
}