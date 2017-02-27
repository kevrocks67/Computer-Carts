Public Class Form1
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click

    End Sub

    Private Sub ComboBox1_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox1.SelectedIndexChanged
        ComboBox1.Show()
        ComboBox1.Items.Add("Computer Type")
        ComboBox1.Items.Add("Room Number")
        ComboBox1.Items.Add("Cart Number")
        ComboBox1.Items.Add("Amount of Computers")
    End Sub

    Private WithEvents Form1BindingSource1_CurrentChanged As ComboBox



End Class
