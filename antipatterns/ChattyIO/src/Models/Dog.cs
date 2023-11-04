public class Dog
{
    public Guid Id { get; set; }
    public string Name { get; set; }
    public string Race { get; set; }
    public string Age { get; set; }
    public virtual Owner Owner { get; set; }
}