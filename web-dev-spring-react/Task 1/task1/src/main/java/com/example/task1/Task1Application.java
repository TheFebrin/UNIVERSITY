package com.example.task1;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.*;

import java.util.Arrays;
import java.util.Map;


@RestController
@SpringBootApplication
public class Task1Application {

	@Autowired
	private Register registerService;

	public static void main(String[] args) {
		SpringApplication.run(Task1Application.class, args);
	}

	@GetMapping("/stats")
	public Map<String, Integer> stats(@RequestParam(value = "mode", defaultValue = StatsMode.TOP_THREE) String mode) {
		return registerService.getStats(mode);
	}

	@PostMapping("/register")
	public RegisterUserResponse register(@RequestParam(value = "name") String name) {
		registerService.registerUser(name);
		return new RegisterUserResponse("OK", registerService.getCountForUser(name));
	}

	@DeleteMapping("/delete")
	public void delete(@RequestParam(value = "name") String name) {
		registerService.deleteUser(name);
	}
}
