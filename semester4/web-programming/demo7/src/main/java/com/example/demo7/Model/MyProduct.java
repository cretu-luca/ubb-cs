package com.example.demo7.Model;

import jakarta.persistence.*;

@Entity
@Table(name = "MyProduct")
public class MyProduct {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public int Id;
    public String Name;
    public double Price;
}
