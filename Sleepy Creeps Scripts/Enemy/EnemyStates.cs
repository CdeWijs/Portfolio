using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnemyStates : MonoBehaviour
{
    public LayerMask detectionLayer;

    private AutoIntensity autoIntensity;
    private EnemyController enemyController;
    private Collider[] moveCollider;
    private float moveRadius = 20;

    private void Start ()
    {
        
        autoIntensity = FindObjectOfType<AutoIntensity>();
        enemyController = FindObjectOfType<EnemyController>();
	}

    public void IdleState(GameObject enemy)
    {
        Animator animator = enemy.GetComponent<Animator>();
        NavMeshAgent agent = enemy.GetComponent<NavMeshAgent>();
        
        animator.SetBool("isIdle", true);
        animator.SetBool("isMoving", false);
        animator.SetBool("isSleeping", false);

        if (agent.enabled == true)
        {
            moveCollider = Physics.OverlapSphere(enemy.transform.position, moveRadius, detectionLayer);

            if (moveCollider.Length > 0)
            {
                enemyController.currentState = EnemyController.State.MOVE;
            }
        }

        if (autoIntensity.dot > 0)
        {
            enemyController.currentState = EnemyController.State.SLEEP;
        }
    }

    public void MoveState(GameObject enemy)
    {
        Animator animator = enemy.GetComponent<Animator>();
        NavMeshAgent agent = enemy.GetComponent<NavMeshAgent>();
        
        agent.SetDestination(moveCollider[0].transform.position);
        animator.SetBool("isIdle", false);
        animator.SetBool("isMoving", true);
        animator.SetBool("isSleeping", false);

        for (int i = 0; i < moveCollider.Length; i++)
        {
            if (moveCollider[i] == null)
            {
                enemyController.currentState = EnemyController.State.IDLE;
            }
        }

        if (autoIntensity.dot > 0)
        {
            enemyController.currentState = EnemyController.State.SLEEP;
        }
    }

    public void SleepState(GameObject enemy)
    {
        Animator animator = enemy.GetComponent<Animator>();
        NavMeshAgent agent = enemy.GetComponent<NavMeshAgent>();
        
        animator.SetBool("isSleeping", true);
        animator.SetBool("isMoving", false);
        animator.SetBool("isIdle", false);

        if (autoIntensity.dot <= 0)
        {
            enemyController.currentState = EnemyController.State.IDLE;
        }
    }
}
