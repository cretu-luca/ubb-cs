package com.example.demo6.Model;

import jakarta.persistence.*;

@Entity
@Table(name = "Products")
public class Products {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public int Id;
    public String Name;
    public String Description;
}
