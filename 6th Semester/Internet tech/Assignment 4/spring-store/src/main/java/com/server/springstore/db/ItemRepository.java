package com.server.springstore.db;

import java.util.List;

import com.server.springstore.model.Item;

import org.springframework.data.jpa.repository.JpaRepository;

public interface ItemRepository extends JpaRepository<Item, Long> {
    List<Item> findByCtype(String ctype);
}
