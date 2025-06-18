package com.example.demo4.Model;

import jakarta.persistence.*;

@Entity
@Table(name = "Document")
public class Document {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public int Id;
    public String Name;
    public String Contents;
}
