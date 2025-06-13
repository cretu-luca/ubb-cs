using System.ComponentModel.DataAnnotations;

namespace asp_dotnet.Model;

public class SoftwareDeveloper
{
    [Key]
    public int Id { get; set; }
    public string Name { get; set; }
    public int Age { get; set; }
    public string Skills { get; set; }
}
