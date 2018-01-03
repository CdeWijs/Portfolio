using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ToggleControls : MonoBehaviour
{
    public GameObject controls;
    public GameObject gameUI;

    public void TurnControlsOff()
    {
        controls.SetActive(false);
        gameUI.SetActive(true);
    }

    public void TurnControlsOn()
    {
        controls.SetActive(true);
        gameUI.SetActive(false);
    }
}
