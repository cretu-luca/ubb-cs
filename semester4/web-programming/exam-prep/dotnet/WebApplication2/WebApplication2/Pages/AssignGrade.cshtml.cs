using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication2;
using WebApplication2.Models;
using System.Collections.Generic;
using System.Linq;
using System;

namespace MyApp.Namespace
{
    public class AssignGradeModel : PageModel
    {
        private readonly AppDbContext _context;
        public string message; 

        public AssignGradeModel(AppDbContext context)
        {
            _context = context;
        }
        
        public void OnGet()
        {
        }

        public IActionResult OnPost()
        {
            String studentName = Request.Form["studentName"];
            String courseName = Request.Form["courseName"];
            
            // Add error handling for grade parsing
            int grade;
            if (!int.TryParse(Request.Form["grade"], out grade))
            {
                message = "Invalid grade format";
                return Page();
            }
            
            Course course = _context.Courses.FirstOrDefault(c => c.CourseName == courseName);
            Person student = _context.Persons.FirstOrDefault(p => p.Name == studentName);
            
            string username = HttpContext.Session.GetString("username");
            Person user = _context.Persons.FirstOrDefault(p => p.Name == username);

            if (course == null)
            {
                message = "Course not found";
                return Page();
            }
            
            if (course.ProfessorId != user.Id)
            {
                message = "not your course";
                return Page();
            }

            if (student == null)
            {
                message = "student not found";
                return Page();
            }

            bool isParticipant = false;
            
            // Handle null or empty Participants string
            List<string> participantsIds = new List<string>();
            if (!string.IsNullOrEmpty(course.Participants))
            {
                participantsIds = course.Participants.Split(",").ToList();
            }
            
            foreach (String participantId in participantsIds)
            {
                if (!string.IsNullOrEmpty(participantId) && participantId.Trim() == student.Id.ToString())
                {
                    isParticipant = true;
                    break;
                }
            }

            if (!isParticipant)
            {
                participantsIds.Add(student.Id.ToString());
                course.Participants = String.Join(",", participantsIds);

                String grades = course.Grades;
                grades = grades + grade.ToString() + "-" + student.Id + ",";
                
                course.Grades = grades;
                
                _context.Courses.Update(course);
                _context.SaveChanges();
                message = "Student added to course";
            }
            else
            {
                // already a participant 
                // check for grade 
                
                List<String> newGrades = new List<String>();
                
                // Handle null or empty Grades string
                if (!string.IsNullOrEmpty(course.Grades))
                {
                    string[] grades = course.Grades.Split(",", StringSplitOptions.RemoveEmptyEntries);
                    bool gradeUpdated = false;
                    
                    foreach (String gradeEntry in grades)
                    {
                        if (string.IsNullOrWhiteSpace(gradeEntry)) continue;
                        
                        string[] parts = gradeEntry.Split("-");
                        if (parts.Length != 2) continue;
                        
                        int gradeFound;
                        int idFound;
                        
                        if (!int.TryParse(parts[0], out gradeFound) || !int.TryParse(parts[1], out idFound))
                            continue;

                        if (idFound == student.Id)
                        {
                            newGrades.Add(grade + "-" + idFound);
                            gradeUpdated = true;
                        }
                        else
                        {
                            newGrades.Add(gradeEntry);
                        }
                    }
                    
                    // If we didn't update an existing grade, add a new one
                    if (!gradeUpdated)
                    {
                        newGrades.Add(grade + "-" + student.Id);
                    }
                }
                else
                {
                    // No grades yet, add the first one
                    newGrades.Add(grade + "-" + student.Id);
                }
                
                course.Grades = String.Join(",", newGrades);
                
                _context.Courses.Update(course);
                _context.SaveChanges();
                message = "Grade assigned successfully";
            }

            return Page();
        }
    }
}
