package com.example.demo5.Model;

import jakarta.persistence.*;

@Entity
@Table(name = "Journal")
public class Journal {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public int Id;
    public String Name;
}
