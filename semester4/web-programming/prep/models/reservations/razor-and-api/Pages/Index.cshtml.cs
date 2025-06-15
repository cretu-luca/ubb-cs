using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using asp_dotnet.Repository;
using asp_dotnet.Model;

namespace razor_and_api.Pages;

public class IndexModel : PageModel
{
    private readonly IReservationRepository _repository;
    
    public string Message { get; set; }

    [BindProperty]
    public string Name { get; set; }
    
    [BindProperty]
    public DateTime Date { get; set; }
    
    [BindProperty]
    public string City { get; set; }

    public IndexModel(IReservationRepository repository)
    {
        _repository = repository;
    }

    public void OnGet()
    {
    }

    public async Task<IActionResult> OnPostAsync()
    {
        if (string.IsNullOrEmpty(Name) || string.IsNullOrEmpty(City))
        {
            Message = "Please fill in all fields";
            return Page();
        }

        var reservation = new Reservation
        {
            person = Name,
            Type = "Pending",
            idReservedResource = 0
        };

        await _repository.AddAsync(reservation);
        
        Message = $"Reservation created for {Name} to {City} on {Date.ToString("yyyy-MM-dd")}";
        return Page();
    }
}
