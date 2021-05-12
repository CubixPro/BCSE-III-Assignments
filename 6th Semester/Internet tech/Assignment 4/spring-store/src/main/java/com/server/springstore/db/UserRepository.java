package com.server.springstore.db;

import com.server.springstore.model.User;

import org.springframework.data.jpa.repository.JpaRepository;

public interface UserRepository extends JpaRepository<User, Long>{
    User findByEmail(String email);
}
