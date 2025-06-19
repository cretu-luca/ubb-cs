package com.example.demo6.Model;

import jakarta.persistence.*;

@Entity
@Table(name = "ProductsOrders")
public class ProductsOrders {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public int Id;
    public String user;
    public int ProductId;
    public int Quantity;
}
