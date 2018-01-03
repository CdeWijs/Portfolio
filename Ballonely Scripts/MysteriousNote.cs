using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MysteriousNote : MonoBehaviour {

	public GameObject readNote;
	public GameObject mysteriousNote;

	private bool isInTrigger = false;

	private void Update ()
    {

		if (isInTrigger)
        {

			if (Input.GetKeyDown(KeyCode.E))
            {
				readNote.SetActive(false);
				mysteriousNote.SetActive(true);
				readNote.SetActive(false);
				Time.timeScale = 0;
			} 

			if (Input.GetKeyDown(KeyCode.Z))
            {
				mysteriousNote.SetActive(false);
				Time.timeScale = 1;
				readNote.SetActive(true);
			}

		}
        else
        {
			readNote.SetActive(false);
			mysteriousNote.SetActive(false);
		}
	}

	private void OnTriggerEnter (Collider col)
    {
		if (col.gameObject.CompareTag("Player"))
        {
			isInTrigger = true;
			readNote.SetActive(true);
		}
	}

	private void OnTriggerExit (Collider col)
    {
        // If col is a Player
		if (col.gameObject.CompareTag("Player"))
        {
			isInTrigger = false;
		}
	}
}
