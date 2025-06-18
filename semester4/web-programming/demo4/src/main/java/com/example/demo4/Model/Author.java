package com.example.demo4.Model;

import jakarta.persistence.*;

@Entity
@Table(name = "Author")
public class Author {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public int Id;
    public String Name;
    public String DocumentList;
    public String MovieList;
}
