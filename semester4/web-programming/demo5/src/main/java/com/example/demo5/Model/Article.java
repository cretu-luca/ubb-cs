package com.example.demo5.Model;

import jakarta.persistence.*;

import java.time.LocalDate;
import java.util.Date;

@Entity
@Table(name = "Article")
public class Article {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public int id;
    public String User;
    public int JournalId;
    public String Summary;
    public LocalDate Date;
}
