package com.example.lab09forward.repository.file;

import com.example.lab09forward.domain.Entities.Entity;
import com.example.lab09forward.domain.validators.Validator;
import com.example.lab09forward.repository.memory.InMemoryRepository0;

import java.io.*;

import java.util.Arrays;
import java.util.List;


///Aceasta clasa implementeaza sablonul de proiectare Template Method; puteti inlucui solutia propusa cu un Factori (vezi mai jos)

/**
 * Abstract class models File Repository
 *
 * @param <ID> - type of id
 * @param <E>  - type of entity
 */
public abstract class AbstractFileRepository0<ID, E extends Entity<ID>> extends InMemoryRepository0<ID, E> {
    /**
     * fileName class member
     *
     * @type - String
     */
    String fileName;

    /**
     * Constructor for AbstractFileRepository0
     *
     * @param fileName  - String
     * @param validator - Validator
     */
    public AbstractFileRepository0(String fileName, Validator<E> validator) {
        super(validator);
        this.fileName = fileName;
        loadData();

    }

    /**
     * Method to load data from file
     */
    private void loadData() {
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String linie;
            while ((linie = br.readLine()) != null) {
                List<String> attr = Arrays.asList(linie.split(","));
                E e = extractEntity(attr);
                super.save(e);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        //sau cu lambda - curs 4, sem 4 si 5
//        Path path = Paths.get(fileName);
//        try {
//            List<String> lines = Files.readAllLines(path);
//            lines.forEach(linie -> {
//                E entity=extractEntity(Arrays.asList(linie.split(";")));
//                super.save(entity);
//            });
//        } catch (IOException e) {
//            e.printStackTrace();
//        }

    }

    /**
     * extract entity  - template method design pattern
     * creates an entity of type E having a specified list of @code attributes
     *
     * @param attributes - List of String
     * @return an entity of type E
     */
    public abstract E extractEntity(List<String> attributes);
    ///Observatie-Sugestie: in locul metodei template extractEntity, puteti avea un factory pr crearea instantelor entity

    /**
     * Method to create entity as a string
     *
     * @param entity - Entity
     * @return - String representation of entity
     */
    protected abstract String createEntityAsString(E entity);

    /**
     * Method to save entity to repository
     *
     * @param entity entity must be not null
     * @return - null- if the given entity is saved
     */
    @Override
    public E save(E entity) {
        E e = super.save(entity);
        if (e == null) {
//            writeToFile(entity);
        }


        return e;

    }

    /**
     * Method to write entity to file
     *
     * @param entity - E
     */
    protected void writeToFile(E entity) {
        try (BufferedWriter bW = new BufferedWriter(new FileWriter(fileName, true))) {
            bW.write(createEntityAsString(entity));
            bW.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    protected void writeFile() {
        try (BufferedWriter bW = new BufferedWriter(new FileWriter(fileName))) {
            for (E entity : findAll()) {
                bW.write(createEntityAsString(entity));
                bW.newLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
