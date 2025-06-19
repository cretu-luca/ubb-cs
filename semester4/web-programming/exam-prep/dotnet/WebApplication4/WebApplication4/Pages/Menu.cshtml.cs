using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace MyApp.Namespace
{
    public class MenuModel : PageModel
    {
        public void OnGet()
        {
        }

        public IActionResult OnPostFlights()
        {
            return RedirectToPage("/Flight");
        }

        public IActionResult OnPostHotels()
        {
            return RedirectToPage("/Hotel");
        }
    }
}
