// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract StudentData {
    // Define a structure for Student
    struct Student {
        uint id;
        string name;
        uint grade;
    }

    // Array to store Student records
    Student[] public students;

    // Mapping to keep track of existing student IDs
    mapping(uint => bool) private studentExists;

    // Event to notify when a new student is added
    event StudentAdded(uint id, string name, uint grade);

    // Function to add a new student
    function addStudent(uint _id, string memory _name, uint _grade) public {
        require(!studentExists[_id], "Student with this ID already exists");
        Student memory newStudent = Student(_id, _name, _grade);
        students.push(newStudent);
        studentExists[_id] = true;
        emit StudentAdded(_id, _name, _grade);
    }

    // Function to retrieve a student's information by their index in the array
    function getStudent(uint _index) public view returns (uint, string memory, uint) {
        require(_index < students.length, "Invalid student index");
        Student memory s = students[_index];
        return (s.id, s.name, s.grade);
    }

    // Fallback function to handle unexpected transactions
    fallback() external payable {
        // Can include some logging if needed
    }
}
