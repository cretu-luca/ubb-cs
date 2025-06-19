using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication3;
using WebApplication3.Models;

namespace MyApp.Namespace
{
    public class SearchSkillsModel : PageModel
    {
        private readonly AppDbContext _context;
        public ICollection<SoftwareDeveloper> Persons { get; set; }

        public SearchSkillsModel(AppDbContext context)
        {
            this._context = context;
            Persons = new List<SoftwareDeveloper>();
        }
        
        public void OnGet()
        {
            Persons = new List<SoftwareDeveloper>();
        }

        public void OnPost()
        {
            String skill = Request.Form["skill"];
            List<SoftwareDeveloper> persons = _context.Developers.ToList();
            List<SoftwareDeveloper> newPersons = new List<SoftwareDeveloper>();
            
            Console.WriteLine(skill);
            
            foreach (var person in persons) 
            {
                if (person.Skills.Contains(skill))
                {
                    newPersons.Add(person);
                }
            }
            
            Persons = newPersons;
        }
    }
}
