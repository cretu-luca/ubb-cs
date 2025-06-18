package com.example.demo7;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.Persistence;

import java.util.List;

public class DbManager {
    private static EntityManagerFactory emf;

    static {
        try {
            emf = Persistence.createEntityManagerFactory("examPU");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static EntityManager getEntityManager() {
        return emf.createEntityManager();
    }

    public static <T> T save(T entity) {
        EntityManager em = getEntityManager();
        try {
            em.getTransaction().begin();
            em.persist(entity);
            em.getTransaction().commit();
            return entity;
        } finally {
            em.close();
        }
    }

    public static <T> T findById(Class<T> clazz, int id) {
        EntityManager em = getEntityManager();
        try {
            return em.find(clazz, id);
        } finally {
            em.close();
        }
    }

    public static <T> List<T> findAll(Class<T> clazz) {
        EntityManager em = getEntityManager();
        try {
            return em.createQuery("FROM " + clazz.getSimpleName(), clazz).getResultList();
        } finally {
            em.close();
        }
    }

    public static <T> void update(T entity) {
        EntityManager em = getEntityManager();
        try {
            em.getTransaction().begin();
            em.merge(entity);
            em.getTransaction().commit();
        } finally {
            em.close();
        }
    }

    public static <T> void delete(T entity) {
        EntityManager em = getEntityManager();
        try {
            em.getTransaction().begin();
            em.remove(em.merge(entity));
            em.getTransaction().commit();
        } finally {
            em.close();
        }
    }
}