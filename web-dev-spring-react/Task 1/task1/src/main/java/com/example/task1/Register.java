package com.example.task1;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Service;

import java.util.*;

import static java.lang.Math.min;

@Service
@Scope("singleton")
public class Register {

    private final LinkedHashMap<String, Integer> registeredUsers = new LinkedHashMap<String, Integer>();

    public void registerUser(String name) {
        this.registeredUsers.merge(name, 1, Integer::sum);
    }

    public Integer getCountForUser(String name) {
        Integer currentCount = this.registeredUsers.get(name);
        return currentCount == null ? 0 : currentCount;
    }

    public Map<String, Integer> getRegisteredUsersIgnoreCase() {
        List<Map.Entry<String, Integer>> registeredUsersList = new ArrayList<Map.Entry<String, Integer>>(
                this.registeredUsers.entrySet()
        );
        registeredUsersList.sort(Comparator.comparing(p -> -p.getValue()));

        LinkedHashMap<String, Integer> result = new LinkedHashMap<String, Integer>();
        for (Map.Entry<String, Integer> stringIntegerEntry : registeredUsersList) {
            String currentName = stringIntegerEntry.getKey().toLowerCase();
            Integer currentCount = stringIntegerEntry.getValue();
            result.merge(currentName, currentCount, Integer::sum);
        }
        return result;
    }

    public Map<String, Integer> getRegisteredUsersTopThree() {
        List<Map.Entry<String, Integer>> registeredUsersList = new ArrayList<Map.Entry<String, Integer>>(
                this.registeredUsers.entrySet()
        );
        registeredUsersList.sort(Comparator.comparing(p -> -p.getValue()));

        LinkedHashMap<String, Integer> result = new LinkedHashMap<String, Integer>();

        for(int i = 0; i < min(3, registeredUsersList.size()); i ++) {
            result.put(registeredUsersList.get(i).getKey(), registeredUsersList.get(i).getValue());
        }
        return result;
    }

    public Map<String, Integer> getStats(String mode) {
        if (Objects.equals(mode, StatsMode.ALL)) {
            return this.registeredUsers;
        }
        else if (Objects.equals(mode, StatsMode.TOP_THREE)) {
            return this.getRegisteredUsersTopThree();
        } else if (Objects.equals(mode, StatsMode.IGNORE_CASE)) {
            return this.getRegisteredUsersIgnoreCase();
        }
        else {
            return new LinkedHashMap<String, Integer>();
        }
    }

    public void deleteUser(String name) {
        if (this.registeredUsers.containsKey(name)) {
            this.registeredUsers.put(name, 0);
        }
    }
}